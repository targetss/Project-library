#include <iostream>
#include<string>
#include<ctime>
#include<Windows.h>
#include<conio.h>
//#include<cstdio>

#define DEBUG_ARRAY 0
#define DEBUG_LIBRARY 1

using namespace std;


class Array
{
public:

    Array(int count_sensor, int count_elem) : count_sensor(count_sensor), count_elem(count_elem), num_elem(0), time_now(time(NULL)), data(false)
    {
        arr = new int* [count_sensor];
        for (int i = 0; i < count_sensor; i++)
        {
            arr[i] = new int[count_elem] {};
        }

    }

    Array() : arr(nullptr), count_sensor(count_sensor), count_elem(count_elem), num_elem(0), time_now(time(NULL)), data(false)
    {

    }

    bool UpdateAverageData()
    {
        if (this->data)
        {
            data = false;
            return true;
        }
        return false;
    }

    void Update()
    {
        int tt = (time(NULL) - time_now);
        if (tt > ((10 / count_elem)))
        {
            if (num_elem >= count_elem)
            {
                num_elem = 0;
                data = true;
            }
            time_now = time(NULL);
            for (int i = 0; i < count_sensor; i++)
            {
                arr[i][num_elem] = rand() % 10;
            }
            num_elem++;
            ShowArray();
        }

    }

    void ShowArray()
    {
        cout << "Array main:" << endl;
        for (int i = 0; i < count_sensor; i++)
        {
            for (int j = 0; j < count_elem; j++)
            {
                cout << this->arr[i][j] << '\t';
            }
            cout << endl;
        }
    }

    /// <summary>
    /// Возвращает среднее значение со всех датчиков
    /// </summary>
    /// <returns>int - среднее значение со всех датчиков</returns>
    int Average_value()
    {
        int count = 0;
        for (int i = 0; i < count_sensor; i++)
        {
            for (int j = 0; j < count_elem; j++)
            {
                count += arr[i][j];
            }
        }
        return count / (count_sensor + count_elem);
    }

    Array(const Array& other)
    {
        this->count_sensor = other.count_sensor;
        this->count_elem = other.count_elem;
        this->num_elem = other.num_elem;
        this->time_now = other.time_now;
        this->data = other.data;

        this->arr = CreateArr();

        for (int i = 0; i < this->count_sensor; i++)
        {
            for (int j = 0; j < this->count_elem; j++)
            {
                cout << "this arr = " << arr[i][j] << '\t' << "other.arr = " << arr[i][j] << endl;
                this->arr[i][j] = other.arr[i][j];
            }
            cout << endl;
        }
    }

    Array& operator = (const Array& other)
    {
        if (this->arr != nullptr)
        {
            for (int i = 0; i < count_sensor; i++)
            {
                delete[] this->arr[i];
            }
            delete[] this->arr;
            arr = nullptr;
        }

        this->count_sensor = other.count_sensor;
        this->count_elem = other.count_elem;
        this->num_elem = other.num_elem;
        this->time_now = other.time_now;
        this->data = other.data;

        this->arr = this->CreateArr();

        for (int i = 0; i < count_sensor; i++)
        {
            for (int j = 0; j < count_elem; j++)
            {
                this->arr[i][j] = other.arr[i][j];
            }
        }

        return *this;
    }

    Array operator + (const Array& other) //возвращается не ссылка потому что this это левый операнд, а other это правый и поэтому равняться будет новому объекту, который мы создаем в самом методе(временный)
    {
        Array temp;
        if (this->count_elem == other.count_elem)
        {
            temp.count_sensor = this->count_sensor;
            temp.count_elem = this->count_elem;
            temp.num_elem = this->num_elem;
            temp.time_now = this->time_now;
            temp.data = this->data;

            temp.arr = new int* [this->count_sensor];
            for (int i = 0; i < count_sensor; i++)
            {
                temp.arr[i] = new int[count_elem];
            }

            for (int i = 0; i < count_sensor; i++)
            {
                for (int j = 0; j < count_elem; j++)
                {
                    temp.arr[i][j] = this->arr[i][j] + other.arr[i][j];
                }
            }
        }
        else
        {
            temp.count_sensor = this->count_sensor;
            temp.count_elem = this->count_elem;
            temp.num_elem = this->num_elem;
            temp.time_now = this->time_now;
            temp.data = this->data;

            temp.arr = new int* [this->count_sensor];
            for (int i = 0; i < count_sensor; i++)
            {
                temp.arr[i] = new int[count_elem];
            }

            for (int i = 0; i < count_sensor; i++)
            {
                for (int j = 0; j < count_elem; j++)
                {
                    temp.arr[i][j] = this->arr[i][j] + other.arr[i][j];
                }
            }
        }
        return temp;

    }

    Array& operator ++ () //префиксная инкремнт ++А
    {
        for (int i = 0; i < this->count_sensor; i++)
        {
            for (int j = 0; j < this->count_elem; j++)
            {
                arr[i][j]++;
            }
        }
        return *this;
    }

    Array& operator ++(int value) //постфиксная, передаваемый параметр для отличия префикса от постфикса
    {
        Array temp(*this);

        for (int i = 0; i < this->count_sensor; i++)
        {
            for (int j = 0; j < this->count_elem; j++)
            {
                arr[i][j]++;
            }
        }

        return temp;
    }

    int*& operator [](int index1)
    {
        if (index1 >= 0 && index1 < count_sensor)
        {
            return arr[index1];
        }
        else
        {
            cout << "Error: вне границ массива" << endl;
            //return NULL;
        }
    }

    bool operator == (const Array& other)
    {
        bool equality = true;

        if (this->count_sensor != other.count_sensor)
        {
            return false;
        }

        for (int i = 0; i < count_sensor; i++)
        {
            for (int j = 0; j < count_elem; j++)
            {
                this->arr[i][j] != other.arr[i][j] ? equality = false : NULL;
                if (equality == false)
                {
                    return false;
                }
            }
        }

        return true;

    }

    bool operator != (const Array& other)
    {
        bool equality = true;

        if (this->count_sensor != other.count_sensor)
        {
            return true;
        }

        for (int i = 0; i < count_sensor; i++)
        {
            for (int j = 0; j < count_elem; j++)
            {
                this->arr[i][j] == other.arr[i][j] ? equality = false : equality = true;
                if (equality == true)
                {
                    return true;
                }
            }
        }

        return false;
    }


    ~Array()
    {
        for (int i = 0; i < count_sensor; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
        arr = nullptr;
    }

private:
    int** arr;
    int count_sensor; //Кол-во датчиков
    int count_elem; //Кол-во обновлений в минуту, т.е кол-во элементов массива
    int num_elem; //Колво заполненных элементов массива

    int time_now;
    bool data;

    int** CreateArr()
    {
        arr = new int* [count_sensor] {};
        for (int i = 0; i < count_sensor; i++)
        {
            arr[i] = new int[count_elem] {};
        }

        return arr;
    }
};

class Library
{
public:

    Library() : name_(new char[70]{ "NoName" }), author_(new char[70]{ "NoAuthor" }), genre_(new char[70]{ "NoGenre" }), count(0), year(2000)
    {
        //cout << "Сработал конструктор, " << this << endl;
    }


    Library(const char* name, const char* genre, const char* author, int year = NULL, int count = 0)
    {
        strcpy_s(name_ = new char[strlen(name) + 1], strlen(name) + 1, name);
        strcpy_s(genre_ = new char[strlen(genre) + 1], strlen(genre) + 1, genre);
        (author == "") ? strcpy_s(author_ = new char[strlen(author) + 1], strlen(author) + 1, author) : strcpy_s(this->author_ = new char[strlen(author) + 1], strlen(author) + 1, author);;
        (year == NULL) ? this->year = 0 : this->year = year;
        this->count = count;
    }

    Library(const Library& other)
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

    char* GetAuthor()
    {
        return author_;
    }

    char* GetName()
    {
        return name_;
    }

    char* GetGenre()
    {
        return genre_;
    }

    int GetYear()
    {
        return year;
    }

    int GetCount()
    {
        return count;
    }

    Library& operator = (const Library& lb)
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

    bool operator == (const Library& other)
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

    bool operator != (const Library& other)
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

    Library& operator ++()
    {
        this->count++;
        return *this;
    }

    Library& operator++ (int value)
    {
        Library temp(*this);

        this->count++;

        return temp;
    }

    Library operator + (const Library& other)
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

    Library& operator + (int count)
    {
        this->count += count;
        return *this;
    }



    void EditInformationBook()
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

    ~Library()
    {
        //cout << "Сработал деструктор, " << this << endl;
        delete name_, author_, genre_;
    }
private:

    int CountElem(char* name)
    {
        int count = 0;
        while (name[count] != '\0')
        {
            count++;
        }
        return ++count;
    }

    char* name_;
    char* author_;
    char* genre_;
    int year;
    int count;

    friend void PrintBook(const Library& const value); //дружественная функция, доступны private поля вне класса
};

/* Прототипы функций */
void SearchBook(Library* const, const char* const, int);
bool SearchWordInPhrase(const char* const, const char* const);
int CountElementInWord(const char*);
void ShowCatalog(const Library* const, const int);
void CheckPasswd();
void JobMain();

template<typename T>
void DeleteDynamicMemory(T* value)
{
    delete[] value;
    value = nullptr;
}
/* Прототипы функций */

void PrintBook(const Library& const value)
{
    cout << string(200, '=') << endl;

    cout << "|" << string((70 - CountElementInWord(value.name_) / 2), ' ') << value.name_ << string((70 - CountElementInWord(value.name_) / 2), ' ') << "|"
        << string((70 - CountElementInWord(value.author_) / 2), ' ') << value.author_ << string((70 - CountElementInWord(value.author_) / 2), ' ') << "|"
        << string((70 - CountElementInWord(value.genre_) / 2), ' ') << value.genre_ << string((70 - CountElementInWord(value.genre_) / 2), ' ') << "|"
        << string((3), ' ') << value.year << string(3, ' ') << "|"
        << string((3), ' ') << value.count << string(3, ' ') << "|" << endl;
    //cout << "|\t" << value.name_ << "\t|\t" << value.author_ << "\t|\t" << value.genre_ << "\t|\t" << value.year << "\t|\t" << value.count << "\t|" << endl;

    cout << string(72, '=') << endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    srand(time(NULL));


#if DEBUG_LIBRARY
    CheckPasswd();
    JobMain();

#elif DEBUG_ARRAY

    Array ar1(2, 5);

    Array ar2(2, 5);

    Array ar3;
    ar3 = ar1 + ar2;

    cout << *ar3[5];

    while (true)
    {
        ar1.Update();
        if (ar1.UpdateAverageData())
        {
            cout << "Average count: " << ar1.Average_value() << endl;
        }
    }

#endif

    return 0;
}

void JobMain()
{
    char val;
    //char exx;
    int count_book = 0; //общая сумма уникальных книг
    Library* catalog = nullptr;

    do {
        cout << "Введите:" << '\n' << "1 - Поступление новых книг" << endl;
        cout << "2 - Редактирование существующей книги" << endl;
        cout << "3 - Удаление книги из каталога" << endl;
        cout << "4 - Поиск книги в каталоге" << endl;
        cout << "5 - Показать каталог" << endl;

        std::cin >> val;

        switch (val)
        {
        case '1':
            int count_book_add;
            cout << "\x1B[2J\x1B[H"; //очистка консоли
            cout << "========Поступление книг========" << endl;
            cout << "Введите кол-во уникальных книг:" << endl;

            std::cin >> count_book_add;

            if (catalog == nullptr)
            {
                count_book = count_book_add;

                catalog = new Library[count_book];

                cout << catalog[0].GetCount();
                for (int i = 0; i < count_book; i++)
                {
                    catalog[i].EditInformationBook();
                }

                //Library c = catalog[0] + catalog[1];
                //cout << c.GetCount();
            }
            else
            {
                Library* temporary_catalog = new Library[count_book];
                for (int i = 0; i < count_book; i++)
                {
                    temporary_catalog[i] = catalog[i];
                }

                delete[] catalog;
                catalog = nullptr;

                Library* catalog = new Library[count_book_add + count_book];
                count_book += count_book_add;

                for (int i = 0; i < count_book; i++)
                {
                    if (i < count_book - count_book_add)
                    {
                        catalog[i] = temporary_catalog[i];
                    }
                    else
                    {
                        catalog[i].EditInformationBook();
                    }
                }
                delete[] temporary_catalog;
                temporary_catalog = nullptr;
            }

            break;
        case '2':

            break;
        case '3':

            break;
        case '4':
            cin.ignore(cin.rdbuf()->in_avail()); //в потоке остаются символы '\n', поэтому тут надо почистить буфер
            char search_word[100];
            cout << "\x1B[2J\x1B[H"; //очистка консоли
            cout << "========Поиск книги========" << endl;
            cout << "Введите ключевое слово для поиска:" << endl;
            cin.getline(search_word, 100, '\n');

            SearchBook(catalog, search_word, count_book);

            break;
        case '5':
            ShowCatalog(catalog, count_book);
            break;
        }

        //cin >> exx;
    } while (true);

    //ОБЯЗАТЕЛЬНО удалять динамически выделенную память для масиива объектов класса, иначе НЕ СРАБОТАЕТ деструктор!!!
    delete[] catalog;
}

void CheckPasswd()
{
    // Виртуальное нажатие клавиш ALT+ENTER //
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);

    const char truepasswd[] = "qweASD123";
    char c[50];
    bool pswdcorrect = false;

    while (pswdcorrect != true)
    {
        cout << "Введите пароль для входа:" << endl;
        cin >> c;
        if (!strcmp(truepasswd, c))
        {
            pswdcorrect = true;
        }
        else
        {
            cout << "Password incorrect!" << endl;
            system("TIMEOUT /T 3 /NOBREAK");
            system("cls");
        }
        /*
        c = _getch();
        if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c >= 'A' && c <= 'Z')
        {
            c = '*';
            cout << c;
        }
        else if (c == '\r')
        {
            break;
        }*/
    }
    cout << "Password correct!" << endl;
    system("cls");
}

void ShowCatalog(const Library* const value, const int count)
{
    for (int i = 0; i < count; i++)
    {
        PrintBook(value[i]);
    }
}

void SearchBook(Library* const catalog, const char* const name, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (SearchWordInPhrase(name, catalog[i].GetName()) || SearchWordInPhrase(name, catalog[i].GetAuthor()) || SearchWordInPhrase(name, catalog[i].GetGenre()))
        {
            cout << "Search good: № " << i << endl;
        }
    }
}

bool SearchWordInPhrase(const char* const word, const char* const phrase)
{
    int sum_c = 0; //кол-во символов, которые равны первому символу искомого слова

    int countElemPh = CountElementInWord(phrase); // кол-во символов фразы
    int countElemWo = CountElementInWord(word); // кол-во символов искомого слова
    int* ar = 0;

    // Ищем кол-во вхождений первого символа искомого слова в фразе
    for (int i = 0; i < countElemPh; i++)
    {
        if (*word == phrase[i] && i + countElemWo <= countElemPh)
        {
            sum_c++;
        }
    }

    if (sum_c > 0)
    {
        ar = new int[sum_c];

        int c = 0;

        for (int i = 0; i < countElemPh; i++)
        {
            if (phrase[i] == *word && i + countElemWo <= countElemPh)
            {
                *(ar + c) = i;
                c++;
            }
        }


        char new_str[70];

        for (int i = 0; i < sum_c; i++)
        {
            for (int j = ar[i]; j < countElemWo + ar[i]; j++)
            {
                new_str[j - ar[i]] = phrase[j];
                countElemWo - j == 1 ? new_str[j + 1] = '\0' : NULL;
            }

            if (strcmp(word, new_str) == false)
            {
                DeleteDynamicMemory(ar);
                return true;
            }
        }
    }
    else
    {
        ar = nullptr;
        return false;
    }
    return false;
}


int CountElementInWord(const char* word)
{
    int count = 0;
    while (word[count] != '\0')
    {
        count++;
    }
    return count;
}