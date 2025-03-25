#include <iostream>
using namespace std;

class Book
{
private:
    string title;
    string author;
    int year;
    bool status;
public:
    Book(string title_, string author_, int year_, bool status_){
        title = title_;
        author = author_;
        year = year_;
        status = status_;
    };

    ~Book(){
    };

    string get_title(){
        return title;
    };

    string get_author(){
        return author;
    };

    int get_year(){
        return year;
    };

    bool get_status(){
        return status;
    };
};