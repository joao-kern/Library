#include <iostream>
#include "../DB/sqlite3.h"
#include <vector>
#include <functional>
#include "./book.cpp"
using namespace std;

class System
{
private:
    sqlite3* db;
    int exit = sqlite3_open("../DB/library.db", &db);
    bool flag = false;
    vector<function<void()>> operations;

public:
    System() {
        operations = {
            [this]() { add_book(); },
            [this]() { remove_book(); },
            [this]() { list_books(); },
            [this]() { search_book(); },
            [this]() { update_status_book(); },
            [this]() { finish_program(); }
        };
    }

void exec_operation(int i) {
    if (i >= 0 && i < operations.size()) {
        operations[i]();
    } else {
        cout << "Invalid Operation!" << endl;
    }
};

~System(){
    };

    void run(){
        flag = true;

        while(flag){
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
            exec_operation(op);


        };

    };

    void add_book(){
        cout << "ADD A NEW BOOK TO THE DATABASE" << endl;
        cout << endl;
        cout << "Title: " << endl;
        string title;
        cin >> title;
        cout << "Author: " << endl;
        string author;
        cin >> author;
        cout << "Year: " << endl;
        int year;
        cin >> year;

        string sql = "INSERT INTO BOOKS (TITLE, AUTHOR, YEAR) VALUES ('" + title + "', '" + author + "', " + to_string(year) + ");";

        char* messageError;
        int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "Error trying to add book: " << messageError << endl;
            sqlite3_free(messageError);
        } 
        else {
            cout << "Book added with sucess!" << endl;
        };
    };

    void remove_book(){
        cout << "REMOVE BOOK TO THE DATABASE" << endl;
        cout << endl;
        cout << "TITLE: " << endl;
        string title;
        cin >> title;

        string sql = "DELETE FROM BOOK WHERE TITLE IS '" + title + "';";

        char* messageError;
        int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &messageError);

        if (exit != SQLITE_OK) {
            cerr << "Error trying to remove book: " << messageError << endl;
            sqlite3_free(messageError);
        } 
        else {
            cout << "Book removed with sucess!" << endl;
        };
    };

    void list_books(){

    };

    void search_book(){

    };

    void update_status_book(){

    };

    void finish_program(){

    };
};