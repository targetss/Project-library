#include <iostream>
#include <stdio.h>
#include<string>
#include<ctime>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include "Visitor.h"
#include "Library.h"


#define SA 0
#define USERDATA "C:\\Users\\admin\\source\\repos\\targetss\\Project-library\\Project-library\\auth.dat"
#define LOGFILE "C:\\Users\\admin\\source\\repos\\targetss\\Project-library\\Project-library\\logfile.txt"
#define DEBUG 1

//using namespace std;

struct user
{
    char user[20];
    char passwd[20];
    int rights;
};

/* Прототипы функций */
void SearchBook(Library* const, const char* const, int);
bool SearchWordInPhrase(const char* const, const char* const);
int CountElementInWord(const char*);
void ShowCatalog(const Library* const, const int);
int CheckAuth(); //Проверка учетной записи для аутентификации
void JobMain(); // Основная функция для меню
void AddUser(); //Добавление учетной записи
void EditAccountUser(); //Редактирование учетной записи
void ShowListUsers(); //Просмотр всех учетных записей, только для админов
void WorkUsers(); //Меню для работы с учетными записями
void DeleteUser(); //Удаление учетной записи

template<typename T>
void DeleteDynamicMemory(T* value)
{
    delete[] value;
    value = nullptr;
}
/* Прототипы функций */

void PrintBook(const Library& const value)
{
    Library lb;
    std::cout << string(sizeof(value.name_)+sizeof(value.author_)+sizeof(value.genre_), '=') << endl;

    std::cout << "|" << string(CountElementInWord(value.name_) / 2), ' ') << value.name_ << string((sizeof(lb.name_) - CountElementInWord(value.name_) / 2), ' ') << "|"
        << string((sizeof(lb.author_) - CountElementInWord(value.author_) / 2), ' ') << value.author_ << string((sizeof(lb.author_) - CountElementInWord(value.author_) / 2), ' ') << "|"
        << string((sizeof(lb.genre_) - CountElementInWord(value.genre_) / 2), ' ') << value.genre_ << string((sizeof(lb.genre_) - CountElementInWord(value.genre_) / 2), ' ') << "|"
        << string((3), ' ') << value.year << string(3, ' ') << "|"
        << string((3), ' ') << value.count << string(3, ' ') << "|" << endl;
    //cout << "|\t" << value.name_ << "\t|\t" << value.author_ << "\t|\t" << value.genre_ << "\t|\t" << value.year << "\t|\t" << value.count << "\t|" << endl;

    std::cout << string(72, '=') << endl;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    srand(time(NULL));

    //AddUser();
    //CheckAuth();
    JobMain();

    return 0;
}

void JobMain()
{
#ifdef DEBUG
    AddUser();
#endif 

    int role = CheckAuth();
 
    char val;
    //char exx;
    int count_book = 0; //общая сумма уникальных книг
    Library* catalog = nullptr;

    do {
        system("cls");
        std::cout << string(100, ' ') << "Library" << endl;

        std::cout << "Введите:" << '\n' << "1 - Поступление новых книг" << endl;
        std::cout << "2 - Редактирование существующей книги" << endl;
        std::cout << "3 - Удаление книги из каталога" << endl;
        std::cout << "4 - Поиск книги в каталоге" << endl;
        std::cout << "5 - Показать каталог" << endl;
        if (role)
        {
            std::cout << "6 - Создать учетную запись" << endl;
            std::cout << "7 - Учетные данные" << endl;
        } //Если у пользователя права s administrator

        std::cin >> val;

        switch (val)
        {
        case '1':
            int count_book_add;
            std::cout << "\x1B[2J\x1B[H"; //очистка консоли
            std::cout << "========Поступление книг========" << endl;
            std::cout << "Введите кол-во уникальных книг:" << endl;

            std::cin >> count_book_add;

            if (catalog == nullptr)
            {
                count_book = count_book_add;

                catalog = new Library[count_book];

                for (int i = 0; i < count_book; i++)
                {
                    catalog[i].EditInformationBook();
                }
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
            std::cin.ignore(cin.rdbuf()->in_avail()); //в буфере остаются символы '\n', поэтому тут надо почистить буфер
            char search_word[100];
            std::cout << "\x1B[2J\x1B[H"; //очистка консоли
            std::cout << "========Поиск книги========" << endl;
            std::cout << "Введите ключевое слово для поиска:" << endl;
            std::cin.getline(search_word, 100, '\n');

            SearchBook(catalog, search_word, count_book);

            break;
        case '5':
            ShowCatalog(catalog, count_book);
            break;
#ifdef SA //Если у пользователя права s administrator
        case '6':
            AddUser();
            break;
        case '7':
            WorkUsers();
            break;
#endif
        }

        //cin >> exx;
    } while (true);

    //ОБЯЗАТЕЛЬНО удалять динамически выделенную память для масиива объектов класса, иначе НЕ СРАБОТАЕТ деструктор!!!
    delete[] catalog;
}

int CheckAuth()
{
    // Виртуальное нажатие клавиш ALT+ENTER //
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);

    ifstream usr(USERDATA, ios::binary);
    ofstream log(LOGFILE, ios::app);
    user us;
    char buf[sizeof(us)];
    bool correctdata = false, correctauth = false;
    int count_err = 0;
    char users[20];
    char pswd[20];
    int pos_login = 0; //проверяем на какой позиции стоит принятый логин
    bool fg = true;
    while (correctauth != true)
    {
        while (correctdata != true)
        {
            std::cout << "Логин: ";
            std::cin >> users;
            //cout << "users = " << users << "\nsizeof = " << sizeof(users) << endl;
            usr.seekg(0, usr.beg); //beg(begin) - вернуть в начало файла
            while (fg)
            {
                if (!usr.read((char*)&us, sizeof(user)).eof())
                {
                    //cout << "tellg = " << usr.tellg() << endl;
                    if (!strcmp(us.user, users))
                    {
                        correctdata = true;
                        //cout << "tellgtrue = " << usr.tellg() << endl;
                        pos_login = (sizeof(user) / usr.tellg()) - 1;
                        break;
                    }                 
                }
                else
                {
                    fg = false;
                }
                
            }
            
            usr.clear();
            if (correctdata == false)
            {
                std::cout << "Имя пользователя " << users << " не найдено! Попробуйте снова" << endl;
                fg = true;
            }
        }
        correctdata = false;

        while (correctdata == false)
        {
            if (count_err > 0)
            {
                std::cout << "Password incorrect!" << endl;
            }
            std::cout << endl << "Пароль: " << endl;
            std::cin >> pswd;

            // Чисто для самопонимания можно было бы найти пароль от юзера по его позиции
            //usr.seekg(pos_login * sizeof(user));
            //usr.read((char*)&us, sizeof(user));

            if (strcmp(us.passwd, pswd))
            {
                std::cout << us.passwd << endl;
                count_err++;
                std::cout << "Password incorrect!" << endl;
                system("TIMEOUT /T 1 /NOBREAK");
                system("cls");
                if (count_err >= 4)
                {
                    time_t time_log = time(NULL);
                    tm lg;
                    localtime_s(&lg, &time_log);
                    log << '[' << 1900 + lg.tm_year << "." << 1+ lg.tm_mon << "." << lg.tm_mday << " " << lg.tm_hour <<":"<<lg.tm_min<<":"<<lg.tm_sec<<"] ";
                    log << "Authorization. Incorrect password user \"" << us.user << "\";" << '\n';
                    log.close();
                    std::cout << "Не верный пароль!" << endl << "Программа будет закрыта!" << endl;
                    system("TIMEOUT /T 1 /NOBREAK");
                    keybd_event(VK_MENU, 0x12, 0, 0);
                    keybd_event(VK_F4, 0x73, 0, 0);
                }
            }
            else
            {
                correctdata = true;
                correctauth = true;
            }
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
    //cout << "Password correct!" << endl;
    time_t time_log = time(NULL);
    tm lg;
    localtime_s(&lg, &time_log);
    log << '[' << 1900 + lg.tm_year << "." << 1 + lg.tm_mon << "." << lg.tm_mday << " " << lg.tm_hour << ":" << lg.tm_min << ":" << lg.tm_sec << "] ";
    log << "Authorization. Authorization user account: \"" << us.user << "\";" << '\n';
    log.close();

    usr.close();
    system("cls");
    return us.rights;
}

void EditAccountUser()
{
    int num;
    user usr;
    char pswd[sizeof(usr.passwd)]{};

    ShowListUsers();

    std::cout << "Введите номер учетной записи для смены пароля: ";
    std::cin >> num;
    cin.ignore(cin.rdbuf()->in_avail());

    fstream read(USERDATA, ios::binary | ios::in | ios::out);
    read.seekg(sizeof(user) * num);
    read.read((char*)&usr, sizeof(user));
    
    renewpswd:
    std::cout << "Введите новый пароль: ";
    std::cin.getline(usr.passwd, sizeof(usr.passwd), '\n');
    std::cout << std::endl << "Подтвердите пароль: ";
    std::cin.getline(pswd, sizeof(usr.passwd), '\n');
    if (!strcmp(usr.passwd, pswd))
    {
        std::cout << "Пароль изменен!";
        read.seekp(sizeof(user) * num);
        read.write((char*)&usr, sizeof(user));
    }
    else {
        std::cout << "Пароли не совпадают!" << std::endl;
        goto renewpswd;
    }
    read.close();

}

void AddUser()
{
    user adduser{};
    bool good = false;

    do
    {
        char buf[20];
        char buf2[20];

        addusr:
        std::cout << "Введите имя пользователя: " << endl;
        std::cin >> adduser.user;

        ifstream readauthn(USERDATA, ios::binary);

        if (readauthn)
        {
            user usr;
            char usrbuf[sizeof(usr)];
            bool existenceUser = false;
            while (!readauthn.read((char*)&usr, sizeof(user)).eof())
            {
                if (!strcmp(adduser.user, usr.user))
                {
                    existenceUser = true;
                }
            }
            if (existenceUser)
            {
                std::cout << "Введенное имя пользователя уже используется!\nПопробуйте снова!" << endl;
                system("TIMEOUT /T 3 /NOBREAK");
                system("cls");
                readauthn.close();
                goto addusr;
            }
        }

        EditRight:
        std::cout << "Права пользователя:\n1 - Полные права\n0 - Редактирование каталога" << endl;
        std::cin >> adduser.rights;
        if (adduser.rights != 0 && adduser.rights != 1)
        {
            std::cout << "Некорректное значение для прав пользователя!" << endl;
            goto EditRight;
        }
        std::cout << "Введите пароль:" << endl;
        std::cin >> buf;
        std::cout << "Введите пароль еще раз:" << endl;
        std::cin >> buf2;

        if (!strcmp(buf, buf2))
        {
            strcpy_s(adduser.passwd, sizeof(buf), buf);
            good = true;
        }
        else
        {
            std::cout << "Пароли не совпадают!";
        }      
    } while (!good);

    ofstream auth(USERDATA, ios::binary | ios::app);
    auth.write((char*)&adduser, sizeof(user));
    auth.close();
    
    /*if (readauthn)
    {
        //Так мы получим кол-во байт в файле!!!
        readauthn.seekg(0, readauthn.end);
        int size = readauthn.tellg();
        readauthn.seekg(0, readauthn.beg);
        //Так мы получим кол-во байт в файле!!!
    }*/

    std::cout << "Учетная запись " << adduser.user << " успешно добавлена!";
    system("TIMEOUT /T 2 /NOBREAK");
    system("cls");

}

void ShowListUsers()
{
    //system("cls");
    ifstream read(USERDATA, std::ios::binary);
    user usr;

    int count = 0; //кол-во учетных записей
    int val = 0;

    read.seekg(0, ios::end);
    count = read.tellg() / sizeof(usr);
    read.seekg(0, ios::beg);
    
    std::cout << string(sizeof(user)+5, '=') << endl;
    while(!read.read((char*)&usr, sizeof(user)).eof())
    {
        strlen(usr.user) % 2 == 0 ? std::cout << val << " |" << string((sizeof(usr.user) - strlen(usr.user)) / 2, ' ') << usr.user << string((sizeof(usr.user) - strlen(usr.user)) / 2, ' ') << "|" : std::cout << val << " |" << string((sizeof(usr.user) - strlen(usr.user)) / 2, ' ') << usr.user << string((sizeof(usr.user) - strlen(usr.user)) / 2+1, ' ') << "|";
        strlen(usr.passwd) % 2 == 0 ? std::cout << string((sizeof(usr.passwd) - strlen(usr.passwd)) / 2, ' ') << usr.passwd << string((sizeof(usr.passwd) - strlen(usr.passwd)) / 2, ' ') << "|" : std::cout << string((sizeof(usr.passwd) - strlen(usr.passwd)) / 2, ' ') << usr.passwd << string((sizeof(usr.passwd) - strlen(usr.passwd)) / 2 + 1, ' ') << "|";
        std::cout << string(1, ' ') << usr.rights << string(1, ' ') << "|" << endl;
        std::cout << string(sizeof(user) + 5, '-') << endl;
        val++;
    }
    //std::cout << "count = " << count << endl;
    read.close();
}

void WorkUsers()
{
    char value, exit = 'n';
    while (exit!='e')
    {
        std::cout << "======== Диспетчер учетных данных ========" << endl;
        std::cout << "1 - Просмотр учетных записей" << endl;
        std::cout << "2 - Смена пароля учетной записи" << endl;
        std::cout << "3 - Удаление учетной записи" << endl;
        std::cout << "4 - Выход" << endl;
        std::cin >> value;
        switch (value)
        {
        case '1':
            ShowListUsers();
            break;
        case '2':
            EditAccountUser();
            break;
        case '3':
            DeleteUser();
            break;
        case '4':
            exit = 'e';
            break;
        }
    }
}

void DeleteUser()
{
    ifstream rd(USERDATA, ios::binary);
    rd.seekg(0, ios::end);
    int count = rd.tellg() / sizeof(user);
    rd.close();

    int count_usr;
    cout << "Введите порядковый номер учетной записи для удаления: ";
    cin >> count_usr;
    if (count_usr >= 0 && count_usr < count)
    {
        char* buf = new char[sizeof(user) * (count -1)];
        fstream wr(USERDATA, ios::binary | ios::in | ios::out);
        wr.seekg(0, ios::beg);
        user usr1;

        int w = 0, s = 0;
        while (true)
        {
            if (wr.eof()) break;
            if (s >= sizeof(user) * count_usr && s < sizeof(user) * (count_usr + 1))
            {
                s++;
                wr.seekg(sizeof(user) * (count_usr + 1));
                continue;
            }
            wr >> buf[w];
            cout << buf[w];
            w++;
            s++;
        }
        wr.close();

        fstream wrr(USERDATA, ios::out | ios::binary);
        wrr.write(buf, sizeof(user) * (count - 1));
        wrr.close();

        delete[] buf;
        buf = nullptr;
    }
}

void ShowCatalog(const Library* const value, const int count)
{
    for (int i = 0; i < count; i++)
    {
        PrintBook(value[i]);
    }
    char ex = 0;
    while (ex != '0')
    {
        cout << "0 - Выход в главное меню" << endl;
        cin >> ex;
    }

}

void SearchBook(Library* const catalog, const char* const name, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (SearchWordInPhrase(name, catalog[i].GetName()) || SearchWordInPhrase(name, catalog[i].GetAuthor()) || SearchWordInPhrase(name, catalog[i].GetGenre()))
        {
            std::cout << "Search good: № " << i << endl;
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