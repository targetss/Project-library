#pragma once
#include<iostream>
#include "Visitor.h"

#define CATALOG_BOOK "C:\\Users\\Администратор\\Desktop\\c_project\\Project-library\\Project-library\\catalog.txt"

using namespace std;

class Library
{
public:

    Library();
    Library(const char* name, const char* genre, const char* author, int year = NULL, int count = NULL);
    Library(const Library& other);

    char* GetAuthor();
    char* GetName();
    char* GetGenre();
    int GetYear();
    int GetCount();

    Library& operator = (const Library& lb);
    bool operator == (const Library& other);
    bool operator != (const Library& other);
    Library& operator ++();
    Library& operator++ (int value);
    Library operator + (const Library& other);
    Library& operator + (int count);

    void EditInformationBook();

    ~Library();
private:

    int CountElem(char* name);

    char* name_;
    char* author_;
    char* genre_;
    int year;
    int count;

    friend void PrintBook(const Library& const value); //дружественная функция, доступны private поля вне класса
    //friend void Visitor::InfoBook(Library& lb);
};

class Book 
{
public:
    Book(const char* name, const char* author, const char* genre, int count)
    {
        if (name_ == nullptr || author_ == nullptr || genre_ == nullptr)
        {
            name_ = new char[strlen(name) + 1];
            author_ = new char[strlen(author) + 1];
            genre_ = new char[strlen(genre) + 1];
        }
        else
        {
            delete[] name_, author_, genre_;
            name_, author_, genre_ = nullptr;

            name_ = new char[strlen(name) + 1];
            author_ = new char[strlen(author) + 1];
            genre_ = new char[strlen(genre) + 1];
        }

        strcpy_s(name_, sizeof(name_), name);
        strcpy_s(author_, sizeof(author_), author);
        strcpy_s(genre_, sizeof(genre_), genre);
        count_ = count;

        ifstream read_book;
        read_book.open(CATALOG_BOOK, ios::in);


    }



    ~Book()
    {
        delete name_, author_, genre_;

    }
private:
    int ID_;
    char* name_;
    char* author_;
    char* genre_;
    int count_;
};