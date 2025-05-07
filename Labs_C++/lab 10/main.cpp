#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// П.6: Пользовательский класс (по заданию)
class Book {
    string title;
    string author;
public:
    Book(string t = "", string a = "") : title(t), author(a) {}
    
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    void setTitle(string t) { title = t; }
    
    void display() const {
        cout << title << " (" << author << ")" << endl;
    }
};

int main() {
    // === Часть 1: Работа с базовым типом (int) ===
    
    // П.2: Создание и заполнение контейнера
    vector<int> numbers = {5, 2, 8, 3, 1};
    
    // П.3: Просмотр контейнера
    cout << "=== Работа с int ===" << endl;
    cout << "Исходный вектор: ";
    for (int n : numbers) cout << n << " ";
    cout << endl << endl;
    
    // П.4: Изменение контейнера
    numbers.erase(remove(numbers.begin(), numbers.end(), 3), numbers.end()); // Удаление элемента 3
    numbers[1] *= 10; // Изменение второго элемента
    
    // П.5: Просмотр через итераторы
    cout << "Измененный вектор: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl << endl;
    
    // === Часть 2: Работа с пользовательским типом (Book) ===
    
    // П.2,6: Создание и заполнение контейнера
    vector<Book> library = {
        Book("1984", "Оруэлл"),
        Book("Преступление и наказание", "Достоевский"),
        Book("Мастер и Маргарита", "Булгаков")
    };
    
    // П.3,6: Просмотр контейнера
    cout << "=== Работа с Book ===" << endl;
    cout << "Исходная библиотека:" << endl;
    for (const Book& b : library) b.display();
    cout << endl;
    
    // П.4,6: Изменение контейнера
    library.erase(library.begin() + 1); // Удаление второй книги
    library[0].setTitle("Новое название"); // Изменение первой книги
    
    // П.5,6: Просмотр через итераторы
    cout << "Измененная библиотека:" << endl;
    for (auto it = library.begin(); it != library.end(); ++it) {
        it->display();
    }
    cout << endl;
    
    
    return 0;
}