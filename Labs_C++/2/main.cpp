#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;

public:
    // Конструкторы
    Book() : title(""), author(""), genre("") {
        cout << "Вызван конструктор Book() без параметров" << endl;
    }
    
    Book(string t, string a) : title(t), author(a), genre("Не указан") {
        cout << "Вызван конструктор Book(string, string) с параметрами" << endl;
    }
    
    Book(string t, string a, string g) : title(t), author(a), genre(g) {
        cout << "Вызван конструктор Book(string, string, string) с параметрами" << endl;
    }
    
    Book(const Book& other) : title(other.title), author(other.author), genre(other.genre) {
        cout << "Вызван конструктор копирования Book(const Book&)" << endl;
    }

    // Деструктор
    ~Book() {
        cout << "Вызван деструктор ~Book() для книги: " << title << endl;
    }

    // Методы
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }

    void display() const {
        cout << "Книга: " << title << " | Автор: " << author << " | Жанр: " << genre << endl;
    }
};

class Library {
private:
    string name;
    string address;
    vector<Book> books;

public:
    // Конструкторы
    Library() : name(""), address("") {
        cout << "Вызван конструктор Library() без параметров" << endl;
    }
    
    Library(string n, string a) : name(n), address(a) {
        cout << "Вызван конструктор Library(string, string) с параметрами" << endl;
    }
    
    Library(const Library& other) : name(other.name), address(other.address), books(other.books) {
        cout << "Вызван конструктор копирования Library(const Library&)" << endl;
    }

    // Деструктор
    ~Library() {
        cout << "Вызван деструктор ~Library() для библиотеки: " << name << endl;
    }

    // Методы
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Метод для пункта 5
    void addNewBook(string title, string author, string genre) {
        Book newBook(title, author, genre);
        books.push_back(newBook);
    }

    // Метод для пункта 6
    void addCopies(const Book& original, int count) {
        for (int i = 0; i < count; i++) {
            books.push_back(Book(original));
        }
    }

    void display() const {
        cout << "Библиотека: " << name << endl;
        cout << "Адрес: " << address << endl;
        cout << "Книги в библиотеке (" << books.size() << "):" << endl;
        
        for (const auto& book : books) {
            book.display();
        }
    }
};

int main() {
    cout << "=== Демонстрация работы конструкторов и деструкторов ===" << endl;
    
    // 1. Создание библиотеки
    cout << "\nСоздание центральной библиотеки:" << endl;
    Library centralLib("Центральная городская библиотека", "ул. Ленина, 10");

    // 2. Создание книг разными конструкторами
    cout << "\nСоздание книг:" << endl;
    Book book1; // Конструктор без параметров
    Book book2("1984", "Дж. Оруэлл"); // Конструктор с 2 параметрами
    Book book3("Мастер и Маргарита", "М. Булгаков", "Фантастика"); // Конструктор с 3 параметрами
    Book book4(book3); // Конструктор копирования

    // 3. Добавление книг в библиотеку
    cout << "\nДобавление книг:" << endl;
    centralLib.addBook(book1);
    centralLib.addBook(book2);
    centralLib.addBook(book3);

    // 4. Использование нового метода (пункт 5)
    cout << "\nДобавление новой книги через addNewBook:" << endl;
    centralLib.addNewBook("Преступление и наказание", "Ф. Достоевский", "Роман");

    // 5. Использование метода для копий (пункт 6)
    cout << "\nДобавление копий книги:" << endl;
    centralLib.addCopies(book2, 2);

    // 6. Создание временной библиотеки
    cout << "\nСоздание временной библиотеки:" << endl;
    {
        Library tempLib;
        tempLib.addNewBook("Война и мир", "Л. Толстой", "Роман");
        tempLib.display();
    } // Здесь вызовется деструктор tempLib

    // 7. Вывод информации о библиотеке
    cout << "\nИтоговое состояние центральной библиотеки:" << endl;
    centralLib.display();

    cout << "\n=== Завершение программы ===" << endl;
    return 0;
}