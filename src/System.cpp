#include "System.h"
#include <iostream>
#include <limits>
#include <stdexcept>

System::System() : flag(false)
{
    if (sqlite3_open("../DB/library.db", &db) != SQLITE_OK)
    {
        std::cerr << "Erro ao abrir o banco: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Falha na conexão com o banco de dados");
    }

    operations = {
        [this]()
        { add_book(); },
        [this]()
        { remove_book(); },
        [this]()
        { list_books(); },
        [this]()
        { search_book(); },
        [this]()
        { update_status_book(); }};
}
System::~System()
{
    sqlite3_close(db);
};

int System::readInt(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Entrada inválida. Digite um número.\n";
        }
        else
        {
            std::cin.ignore();
            return value;
        }
    }
}

std::string System::readString(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
};

void System::exec_operation(int i)
{
    if (i > 0 && i < (operations.size() + 1))
    {
        operations[i - 1]();
    }
    else
    {
        std::cout << "Invalid Operation!" << std::endl;
    }
};

void System::run()
{
    flag = true;

    while (flag)
    {
        std::cout << "LIBRARY SYSTEM" << std::endl;
        std::cout << std::endl;
        std::cout << "1 - Add a new book to the database" << std::endl;
        std::cout << "2 - Remove a book from the database" << std::endl;
        std::cout << "3 - List all books" << std::endl;
        std::cout << "4 - Search a especific book" << std::endl;
        std::cout << "5 - Update book's status" << std::endl;
        std::cout << "6 - Finish program." << std::endl;
        std::cout << std::endl;
        int op = readInt("Operation: ");
        if (op == 6)
        {
            std::cout << "Program finished" << std::endl;
            break;
        }
        std::cout << std::endl;
        exec_operation(op);
        std::cout << std::endl;
    };
};

void System::add_book()
{
    std::cout << "ADD A NEW BOOK TO THE DATABASE" << std::endl;
    std::cout << std::endl;
    std::string title = readString("Title: ");
    std::string author = readString("Author: ");
    int year = readInt("Year: ");
    std::cout << std::endl;

    std::string sql = "INSERT INTO BOOKS (TITLE, AUTHOR, YEAR) VALUES ('" + title + "', '" + author + "', " + std::to_string(year) + ");";

    char *messageError;
    int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error trying to add book: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else
    {
        std::cout << "Book added with sucess!" << std::endl;
    };
};

void System::remove_book()
{
    std::cout << "REMOVE BOOK TO THE DATABASE" << std::endl;
    std::cout << std::endl;
    int id = readInt("ID: ");
    std::cout << std::endl;

    std::string sql = "DELETE FROM BOOKS WHERE ID = '" + std::to_string(id) + "';";

    char *messageError;
    int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error trying to remove book: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else
    {
        std::cout << "Book removed with sucess!" << std::endl;
    };
};

void System::list_books()
{
    std::cout << "BOOKS" << std::endl;
    std::cout << std::endl;
    std::string sql = "SELECT *, CASE WHEN STATUS = 0 THEN 'NOT AVAILABLE' WHEN STATUS = 1 THEN 'AVAILABLE' END AS STATUS_TEXT FROM BOOKS;";
    sqlite3_exec(db, sql.c_str(), callback, 0, 0);
    std::cout << std::endl;
};

void System::search_book()
{
    std::cout << "SEARCH A BOOK" << std::endl;
    std::cout << std::endl;
    int id = readInt("ID: ");
    std::cout << std::endl;
    std::string sql = "SELECT TITLE, AUTHOR, YEAR, CASE WHEN STATUS = 0 THEN 'NOT AVAILABLE' WHEN STATUS = 1 THEN 'AVAILABLE' END AS STATUS FROM BOOKS WHERE ID = '" + std::to_string(id) + "';";
    sqlite3_exec(db, sql.c_str(), callback, 0, 0);
    std::cout << std::endl;
};

void System::update_status_book()
{
    std::cout << "UPDATE BOOK STATUS" << std::endl;
    int id = readInt("ID: ");
    int status = 3;
    while (status != 1 && status != 0)
    {
        status = readInt("STATUS (AVAILABLE[1]| NOT AVAILABLE[0]): ");
    }
    std::cout << std::endl;
    std::string sql = "UPDATE BOOKS SET STATUS = '" + std::to_string(status) + "' WHERE ID = '" + std::to_string(id) + "'";
    char *messageError;
    int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error trying to update status: " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    else
    {
        std::cout << "Status updated with sucess!" << std::endl;
    };
};

int System::callback(void *data, int argc, char **argv, char **colNames)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
};