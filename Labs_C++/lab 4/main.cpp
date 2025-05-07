#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Базовый класс - Книга (дополнительный класс из лаб. работы №1)
class Book {
protected:
    string title;
    string author;
    string genre;

public:
    Book() : title("Без названия"), author("Неизвестен"), genre("Не указан") {}
    Book(string t, string a, string g) : title(t), author(a), genre(g) {}
    virtual ~Book() {}

    // Чисто виртуальная функция (требование п.2)
    virtual void fullDisplay() const = 0;

    // Методы для доступа к данным
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
};

// Класс-наследник - Книга основного зала
class MainHallBook : public Book {
private:
    int shelfNumber;
    bool canBorrow;

public:
    MainHallBook(string t, string a, string g, int sh, bool cb) 
        : Book(t, a, g), shelfNumber(sh), canBorrow(cb) {}

    // Перегрузка виртуальной функции (требование п.3)
    void fullDisplay() const override {
        cout << "=== Книга основного зала ===" << endl;
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Жанр: " << genre << endl;
        cout << "Номер полки: " << shelfNumber << endl;
        cout << "Можно взять домой: " << (canBorrow ? "Да" : "Нет") << endl;
    }
};

// Класс-наследник - Книга читального зала
class ReadingRoomBook : public Book {
private:
    int roomNumber;
    string readerCardRequired;

public:
    ReadingRoomBook(string t, string a, string g, int rn, string rc) 
        : Book(t, a, g), roomNumber(rn), readerCardRequired(rc) {}

    // Перегрузка виртуальной функции (требование п.3)
    void fullDisplay() const override {
        cout << "=== Книга читального зала ===" << endl;
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Жанр: " << genre << endl;
        cout << "Номер зала: " << roomNumber << endl;
        cout << "Требуется читательский билет: " << readerCardRequired << endl;
    }
};

// Основной класс - Библиотека (из лаб. работы №1)
class Library {
private:
    string name;
    string address;
    vector<unique_ptr<Book>> books;  // Модифицированный массив (требование п.6)

public:
    Library(string n, string a) : name(n), address(a) {}

    // Метод для добавления любой книги (модификация для п.6)
    void addBook(unique_ptr<Book> book) {
        books.push_back(move(book));
    }

    // Метод вывода всех данных (требование п.6)
    void displayAll() const {
        cout << "\n=== Информация о библиотеке ===" << endl;
        cout << "Название: " << name << endl;
        cout << "Адрес: " << address << endl;
        cout << "\n=== Книги в библиотеке ===" << endl;
        
        for (const auto& book : books) {
            book->fullDisplay();
            cout << endl;
        }
    }
};

int main() {
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 4 ===" << endl;
    cout << "=== Работа с абстрактными классами и полиморфизмом ===" << endl;

    // 1. Создание массива базового класса (требование п.4)
    vector<unique_ptr<Book>> bookCollection;
    
    // Добавляем объекты разных классов-наследников
    bookCollection.push_back(make_unique<MainHallBook>("1984", "Дж. Оруэлл", "Антиутопия", 5, true));
    bookCollection.push_back(make_unique<ReadingRoomBook>("Война и мир", "Л. Толстой", "Роман", 3, "Да"));
    bookCollection.push_back(make_unique<MainHallBook>("Гарри Поттер", "Дж. Роулинг", "Фэнтези", 7, false));

    // 2. Вывод данных (требование п.5)
    cout << "\nВывод данных из массива:" << endl;
    for (const auto& book : bookCollection) {
        book->fullDisplay();
        cout << endl;
    }

    // 3. Работа с основным классом (требование п.7)
    cout << "\nРабота с классом Library:" << endl;
    Library centralLibrary("Центральная библиотека", "ул. Ленина, 10");
    
    // Добавляем книги разных типов
    centralLibrary.addBook(make_unique<MainHallBook>("Преступление и наказание", "Ф. Достоевский", "Роман", 2, true));
    centralLibrary.addBook(make_unique<ReadingRoomBook>("Энциклопедия", "Разные авторы", "Справочник", 1, "Да"));
    centralLibrary.addBook(make_unique<MainHallBook>("Ревизор", "Н. Гоголь", "Пьеса", 4, false));

    // Выводим все данные
    centralLibrary.displayAll();

    cout << "\n=== Завершение программы ===" << endl;
    return 0;
}