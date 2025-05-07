#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

// Пользовательский тип (из ЛР3)
class Book {
    string title;
    string author;
    int year;
public:
    Book(string t = "", string a = "", int y = 0) 
        : title(t), author(a), year(y) {}
    
    string getTitle() const { return title; }
    int getYear() const { return year; }
    
    // Для сравнения (сортировка)
    bool operator>(const Book& other) const {
        return title > other.title; // Сортировка по названию по убыванию
    }
    
    bool operator<(const Book& other) const {
        return title < other.title; // Сортировка по названию по возрастанию
    }
    
    void display() const {
        cout << title << " (" << author << ", " << year << ")" << endl;
    }
};

int main() {
    // П.2: Создание контейнера (vector)
    vector<Book> library = {
        Book("1984", "Оруэлл", 1949),
        Book("Мастер и Маргарита", "Булгаков", 1967),
        Book("Преступление и наказание", "Достоевский", 1866),
        Book("Война и мир", "Толстой", 1869)
    };

    // П.3: Сортировка по убыванию
    sort(library.begin(), library.end(), greater<Book>());
    
    // П.4: Просмотр после сортировки
    cout << "=== После сортировки по убыванию ===" << endl;
    for (const auto& book : library) {
        book.display();
    }
    cout << endl;

    // П.5: Поиск книг, изданных после 1900 года
    auto condition = [](const Book& b) { return b.getYear() > 1900; };
    
    // П.6: Перемещение в другой контейнер (list)
    list<Book> modernBooks;
    auto it = partition(library.begin(), library.end(), condition);
    modernBooks.assign(library.begin(), it);
    library.erase(library.begin(), it);
    
    // П.7: Просмотр второго контейнера
    cout << "=== Современные книги (после 1900) ===" << endl;
    for (const auto& book : modernBooks) {
        book.display();
    }
    cout << endl;
    
    cout << "=== Остальные книги ===" << endl;
    for (const auto& book : library) {
        book.display();
    }
    cout << endl;

    // П.8: Сортировка обоих контейнеров по возрастанию
    sort(library.begin(), library.end());
    modernBooks.sort();
    
    // П.9: Просмотр после финальной сортировки
    cout << "=== Финальная сортировка по возрастанию ===" << endl;
    cout << "Современные книги:" << endl;
    for (const auto& book : modernBooks) {
        book.display();
    }
    cout << endl;
    
    cout << "Остальные книги:" << endl;
    for (const auto& book : library) {
        book.display();
    }

    return 0;
}