#include <iostream>
#include "../DB/sqlite3.h"
#include <vector>
#include <functional>
using namespace std;
#include <string>
class System
{
private:
    sqlite3 *db;
    int exit = sqlite3_open("../DB/library.db", &db);
    bool flag = false;
    vector<function<void()>> operations;

public:
    System()
    {
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

    void exec_operation(int i)
    {
        if (i > 0 && i < (operations.size() + 1))
        {
            operations[i - 1]();
        }
        else
        {
            cout << "Invalid Operation!" << endl;
        }
    };

    ~System() {
    };

    void run()
    {
        flag = true;

        while (flag)
        {
            cout << "LIBRARY SYSTEM" << endl;
            cout << endl;
            cout << "1 - Add a new book to the database" << endl;
            cout << "2 - Remove a book from the database" << endl;
            cout << "3 - List all books" << endl;
            cout << "4 - Search a especific book" << endl;
            cout << "5 - Update book's status" << endl;
            cout << "6 - Finish program." << endl;
            cout << endl;
            cout << "Operation: " << endl;
            int op;
            cin >> op;
            if (op == 6)
            {
                cout << "Program finished" << endl;
                break;
            }
            cout << endl;
            exec_operation(op);
            cout << endl;
        };
    };

    void add_book()
    {
        cout << "ADD A NEW BOOK TO THE DATABASE" << endl;
        cout << endl;
        cout << "Title: " << endl;
        cin.ignore();
        string title;
        getline(cin, title);
        cout << "Author: " << endl;
        string author;
        getline(cin, author);
        cout << "Year: " << endl;
        string year;
        cin >> year;

        string sql = "INSERT INTO BOOKS (TITLE, AUTHOR, YEAR) VALUES ('" + title + "', '" + author + "', " + year + ");";

        char *messageError;
        int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error trying to add book: " << messageError << endl;
            sqlite3_free(messageError);
        }
        else
        {
            cout << "Book added with sucess!" << endl;
        };
    };

    void remove_book()
    {
        cout << "REMOVE BOOK TO THE DATABASE" << endl;
        cout << endl;
        cout << "Title: " << endl;
        string title;
        getline(cin, title);

        string sql = "DELETE FROM BOOKS WHERE TITLE IS '" + title + "';";

        char *messageError;
        int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error trying to remove book: " << messageError << endl;
            sqlite3_free(messageError);
        }
        else
        {
            cout << "Book removed with sucess!" << endl;
        };
    };

    void list_books()
    {
        cout << "LIST ALL BOOKS" << endl;
        string sql = "SELECT *, CASE WHEN STATUS = 0 THEN 'NOT AVAILABLE' WHEN STATUS = 1 THEN 'AVAILABLE' END AS STATUS_TEXT FROM BOOKS;";
        sqlite3_exec(db, sql.c_str(), callback, 0, 0);
        cout << endl;
    };

    void search_book()
    {
        cout << "SEARCH A BOOK" << endl;
        cout << "Title: " << endl;
        string title;
        cin.ignore();
        getline(cin, title);
        string sql = "SELECT *, CASE WHEN STATUS = 0 THEN 'NOT AVAILABLE' WHEN STATUS = 1 THEN 'AVAILABLE' END AS STATUS_TEXT FROM BOOKS WHERE TITLE LIKE '" + title + "';";
        sqlite3_exec(db, sql.c_str(), callback, 0, 0);
        cout << endl;
    };

    void update_status_book()
    {
        cout << "UPDATE BOOK STATUS" << endl;
        cout << "Title: " << endl;
        string title;
        cin.ignore();
        getline(cin, title);
        string sql = "UPDATE BOOKS SET STATUS = NOT STATUS WHERE TITLE = '" + title + "'";
        char *messageError;
        int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error trying to update status: " << messageError << endl;
            sqlite3_free(messageError);
        }
        else
        {
            cout << "Status updated with sucess!" << endl;
        };
    };

    static int callback(void *data, int argc, char **argv, char **colNames)
    {
        for (int i = 0; i < argc; i++)
        {
            std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        }
        std::cout << std::endl;
        return 0;
    }
};