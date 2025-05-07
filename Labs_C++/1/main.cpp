// Плескачёв А.М. ПИЖ-б-о-23-1(2), Вариант 7

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Дополнительный класс - Книга
class Book {
private:
    string title;
    string author;
    string genre;

public:
    // Два конструктора с разными параметрами (перегрузка)
    Book() : title(""), author(""), genre("") {}
    Book(string t, string a) : title(t), author(a), genre("Не указан") {}
    Book(string t, string a, string g) : title(t), author(a), genre(g) {}

    // Методы для получения данных
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }

    // Метод для вывода информации о книге
    void display() const {
        cout << "Книга: " << title << " | Автор: " << author << " | Жанр: " << genre << endl;
    }
};

// Основной класс - Библиотека
class Library {
private:
    string name;
    string address;
    vector<Book> books;  // Массив объектов дополнительного класса

public:
    Library(string n, string a) : name(n), address(a) {}

    // Метод для добавления книги (принимает объект Book)
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Метод для вывода информации о библиотеке
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
    // Создаем объект основной класс - Библиотека
    Library centralLib("Центральная городская библиотека", "ул. Ленина, 10");

    // Создаем несколько книг разными конструкторами
    Book book1("Преступление и наказание", "Ф. Достоевский", "Роман");
    Book book2("1984", "Дж. Оруэлл"); // Жанр будет "Не указан"
    Book book3("Мастер и Маргарита", "М. Булгаков", "Фантастика");

    // Добавляем книги в библиотеку
    centralLib.addBook(book1);
    centralLib.addBook(book2);
    centralLib.addBook(book3);

    // Выводим информацию о библиотеке и всех книгах
    centralLib.display();

    return 0;
}