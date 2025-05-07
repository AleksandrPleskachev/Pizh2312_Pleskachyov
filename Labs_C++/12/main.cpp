#include <iostream>
#include <vector>
#include <list>
#include <algorithm>  // для sort, copy_if, remove_if, for_each
using namespace std;

// Класс книги (пользовательский тип)
class Book {
    string title;
    string author;
    int year;
public:
    Book(string t = "", string a = "", int y = 0) 
        : title(t), author(a), year(y) {}
    
    // Геттеры
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    
    // Метод вывода
    void display() const {
        cout << "\"" << title << "\" (" << author << ", " << year << ")" << endl;
    }
};

int main() {
    // 1. Создаем и заполняем контейнер vector<Book>
    vector<Book> library = {
        Book("1984", "George Orwell", 1949),
        Book("War and Peace", "Leo Tolstoy", 1869),
        Book("The Master and Margarita", "Mikhail Bulgakov", 1967),
        Book("Crime and Punishment", "Fyodor Dostoevsky", 1866),
        Book("The Hobbit", "J.R.R. Tolkien", 1937)
    };

    // 2. Сортируем по убыванию (по названию) с использованием лямбды
    sort(library.begin(), library.end(), 
        [](const Book& a, const Book& b) {
            return a.getTitle() > b.getTitle();  // Сравнение строк по убыванию
        });

    // 3. Просматриваем отсортированный контейнер с помощью лямбды
    cout << "=== Книги, отсортированные по названию (Z-A) ===" << endl;
    for_each(library.begin(), library.end(), 
        [](const Book& book) {
            book.display();
        });
    cout << endl;

    // 4. Ищем книги, изданные после 1900 года (лямбда-условие)
    auto isModernBook = [](const Book& book) {
        return book.getYear() > 1900;
    };

    // 5. Создаем list и перемещаем в него современные книги
    list<Book> modernBooks;
    copy_if(library.begin(), library.end(), back_inserter(modernBooks), isModernBook);

    // Удаляем современные книги из исходного контейнера
    library.erase(
        remove_if(library.begin(), library.end(), isModernBook),
        library.end()
    );

    // 6. Просматриваем второй контейнер (modernBooks)
    cout << "=== Современные книги (после 1900 года) ===" << endl;
    for_each(modernBooks.begin(), modernBooks.end(), 
        [](const Book& book) {
            book.display();
        });
    cout << endl;

    // 7. Просматриваем первый контейнер (классические книги)
    cout << "=== Классические книги (до 1900 года) ===" << endl;
    for_each(library.begin(), library.end(), 
        [](const Book& book) {
            book.display();
        });
    cout << endl;

    // 8. Сортируем оба контейнера по возрастанию (по названию)
    sort(library.begin(), library.end(), 
        [](const Book& a, const Book& b) {
            return a.getTitle() < b.getTitle();  // Сортировка по возрастанию
        });

    modernBooks.sort([](const Book& a, const Book& b) {
        return a.getTitle() < b.getTitle();
    });

    // 9. Просматриваем отсортированные контейнеры
    cout << "=== Финальная сортировка по возрастанию ===" << endl;
    cout << "Современные книги:" << endl;
    for_each(modernBooks.begin(), modernBooks.end(), 
        [](const Book& book) {
            book.display();
        });
    cout << endl;

    cout << "Классические книги:" << endl;
    for_each(library.begin(), library.end(), 
        [](const Book& book) {
            book.display();
        });
    cout << endl;

    return 0;
}