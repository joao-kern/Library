#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <sqlite3.h>
#include <vector>
#include <functional>
#include <string>

class System
{
private:
    sqlite3 *db;
    bool flag;
    std::vector<std::function<void()>> operations;

    static int callback(void *data, int argc, char **argv, char **colNames);
    int readInt(const std::string &prompt);
    std::string readString(const std::string &prompt);

public:
    System();
    ~System();

    void run();
    void exec_operation(int i);

    void add_book();
    void remove_book();
    void list_books();
    void search_book();
    void update_status_book();
};

#endif