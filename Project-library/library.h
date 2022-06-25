#pragma once
#include<iostream>
#include "Visitor.h"

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