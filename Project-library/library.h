#include<iostream>

using namespace std;

class Library
{
public:

    Library();
    Library(const char* name, const char* genre, const char* author, int year, int count);
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
};

Library::Library() : name_(new char[70]{ "NoName" }), author_(new char[70]{ "NoAuthor" }), genre_(new char[70]{ "NoGenre" }), count(0), year(2000)
{
    //cout << "Сработал конструктор, " << this << endl;
}

Library::Library(const char* name, const char* genre, const char* author, int year = NULL, int count = 0)
{
    strcpy_s(name_ = new char[strlen(name) + 1], strlen(name) + 1, name);
    strcpy_s(genre_ = new char[strlen(genre) + 1], strlen(genre) + 1, genre);
    (author == "") ? strcpy_s(author_ = new char[strlen(author) + 1], strlen(author) + 1, author) : strcpy_s(this->author_ = new char[strlen(author) + 1], strlen(author) + 1, author);;
    (year == NULL) ? this->year = 0 : this->year = year;
    this->count = count;
}

Library::Library(const Library& other)
{
    if (this->name_ != NULL && this->author_ != NULL && this->genre_ != NULL)
    {
        delete name_, author_, genre_;
    }

    strcpy_s(name_ = new char[CountElem(other.name_)], CountElem(other.name_), other.name_);
    strcpy_s(author_ = new char[CountElem(other.author_)], CountElem(other.author_), other.author_);
    strcpy_s(genre_ = new char[CountElem(other.genre_)], CountElem(other.genre_), other.genre_);
    count = other.count;
    year = other.year;

    //cout << "Вызвался конструктор копирования" << this << endl;
}

char* Library::GetAuthor()
{
    return author_;
}

char* Library::GetName()
{
    return name_;
}

char* Library::GetGenre()
{
    return genre_;
}

int Library::GetYear()
{
    return year;
}

int Library::GetCount()
{
    return count;
}

Library& Library::operator = (const Library& lb)
{
    if (this->name_ != nullptr && this->author_ != nullptr && this->genre_ != nullptr)
    {
        //Удаляем динамическую память
        delete[] this->name_;
        delete[] this->author_;
        delete[] this->genre_;
    }

    strcpy_s(this->name_ = new char[CountElem(lb.name_)], CountElem(lb.name_), lb.name_);
    strcpy_s(this->author_ = new char[CountElem(lb.author_)], CountElem(lb.author_), lb.author_);
    strcpy_s(this->genre_ = new char[CountElem(lb.genre_)], CountElem(lb.genre_), lb.genre_);
    this->count = lb.count;
    this->year = lb.year;
    //cout << "Вызвалась перегрузка оператора \"=\"" << endl;
    return *this;
}

bool Library::operator == (const Library& other)
{
    if (strcmp(other.name_, this->name_) + strcmp(other.author_, author_)
        + strcmp(other.genre_, genre_) + (other.year != year)
        + (other.count != count) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Library::operator != (const Library& other)
{
    if (strcmp(other.name_, this->name_) + strcmp(other.author_, author_)
        + strcmp(other.genre_, genre_) + (other.year != year)
        + (other.count != count) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Library& Library::operator ++()
{
    this->count++;
    return *this;
}

Library& Library::operator++ (int value)
{
    Library temp(*this);

    this->count++;

    return temp;
}

Library Library::operator + (const Library& other)
{
    if (!strcmp(this->name_, other.name_)
        && !strcmp(this->author_, other.author_)
        && !strcmp(this->genre_, other.genre_)
        && this->year == other.year)
    {
        Library temp(*this);
        temp.count += other.count;
        return temp;
    }
    else
    {
        cout << "Книги не идентичны" << endl;
        return *this;
    }
}

Library& Library::operator + (int count)
{
    this->count += count;
    return *this;
}



void Library::EditInformationBook()
{
    cin.ignore(cin.rdbuf()->in_avail()); //в буфере остаются символы '\n', поэтому тут надо почистить буфер
    char buf_name[100];
    char buf_author[100];
    char buf_genre[100];
    int buf_year = NULL;
    int buf_count = 0;

    if (name_ == NULL && author_ == NULL && genre_ == NULL)
    {
        cout << "Редактирование данных книги: \"No name" << "\" \"No author\"" << endl;
    }
    else
    {
        cout << "Редактирование данных книги: \"" << name_ << "\", автор: " << author_ << endl;
    }
    cout << '\t' << "Нажмите Enter, если нужно сохранить значение.." << endl;
    cout << "Название книги: ";
    std::cin.getline(buf_name, 100, '\n');
    cout << strlen(buf_name) << endl;
    cout << "Жанр: ";
    std::cin.getline(buf_genre, 100, '\n');
    cout << endl;
    cout << "Автор: ";
    std::cin.getline(buf_author, 100, '\n');
    cout << endl;
    cout << "Год издания: ";
    std::cin >> year;
    cout << endl;
    cout << "Количество на полке: ";
    std::cin >> count;
    cout << endl;

    if (name_ == NULL && author_ == NULL && genre_ == NULL)
    {
        //delete name_, author_, genre_;
        strcpy_s(this->name_ = new char[strlen(buf_name) + 1], strlen(buf_name) + 1, buf_name);
        strcpy_s(this->author_ = new char[strlen(buf_author) + 1], strlen(buf_author) + 1, buf_author);
        strcpy_s(this->genre_ = new char[strlen(buf_genre) + 1], strlen(buf_genre) + 1, buf_genre);
    }
    else
    {
        if (buf_name != "")
        {
            delete name_;
            strcpy_s(this->name_ = new char[strlen(buf_name) + 1], strlen(buf_name) + 1, buf_name);
        }

        if (buf_author != "")
        {
            strcpy_s(this->author_ = new char[strlen(buf_author) + 1], strlen(buf_author) + 1, buf_author);
        }

        if (buf_genre != "")
        {
            strcpy_s(this->genre_ = new char[strlen(buf_genre) + 1], strlen(buf_genre) + 1, buf_genre);
        }
    }

}

Library::~Library()
{
    //cout << "Сработал деструктор, " << this << endl;
    delete name_, author_, genre_;
}

int Library::CountElem(char* name)
{
    int count = 0;
    while (name[count] != '\0')
    {
        count++;
    }
    return ++count;
}