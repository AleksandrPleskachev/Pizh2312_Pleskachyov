#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Базовый класс (ЛР1-4 + новые требования)
class Book {
private:
    static int totalCount; // П.2 - статический счетчик
    string title;
    string author;
    string genre;
    
public:
    // Конструкторы (ЛР3)
    Book() : title(""), author(""), genre("") { ++totalCount; } // П.4
    Book(string t, string a, string g) : title(t), author(a), genre(g) { ++totalCount; } // П.4
    Book(const Book& other) : title(other.title), author(other.author), genre(other.genre) { ++totalCount; } // П.4
    
    // Деструктор (ЛР3)
    virtual ~Book() { --totalCount; } // П.4
    
    // П.3 - статический метод
    static int getTotalCount() { return totalCount; }
    
    // Чисто виртуальная функция (ЛР4)
    virtual void display() const = 0;
    
    // Геттеры (ЛР1-2)
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
};
int Book::totalCount = 0; // Инициализация счетчика

// Класс-наследник 1 (ЛР3)
class MainHallBook : public Book {
    int shelf;
public:
    MainHallBook(string t, string a, string g, int s) 
        : Book(t, a, g), shelf(s) {}
        
    void display() const override {
        cout << "[Основной зал] " << getTitle() << " (" << getGenre() 
             << ") Автор: " << getAuthor() << " | Полка: " << shelf << endl;
    }
};

// Класс-наследник 2 (ЛР3)
class ReadingRoomBook : public Book {
    string section;
public:
    ReadingRoomBook(string t, string a, string g, string s) 
        : Book(t, a, g), section(s) {}
        
    void display() const override {
        cout << "[Читальный зал] " << getTitle() << " (" << getGenre() 
             << ") Автор: " << getAuthor() << " | Раздел: " << section << endl;
    }
};

// Основной класс (ЛР1 + новые требования)
class Library {
private:
    static int storedCount; // П.5 - счетчик в массиве
    string name;
    vector<Book*> books;
    
public:
    Library(string n) : name(n) {}
    
    // П.5 - метод для получения количества
    static int getStoredCount() { return storedCount; }
    
    // Методы из ЛР1-4
    void addBook(Book* book) {
        books.push_back(book);
        ++storedCount; // П.5 - увеличиваем при добавлении
    }
    
    void displayAll() const {
        cout << "=== " << name << " ===\n";
        for(const auto& book : books) {
            book->display();
        }
    }
    
    ~Library() {
        storedCount -= books.size(); // П.5 - корректируем при удалении
        for(auto book : books) delete book;
    }
};
int Library::storedCount = 0; // Инициализация счетчика

int main() {
    // П.6 - вывод без создания объектов
    cout << "Книг всего (до создания): " << Book::getTotalCount() << endl;
    cout << "Книг в библиотеках (до создания): " << Library::getStoredCount() << "\n\n";
    
    // П.7 - создание и добавление объектов
    Library lib("Центральная библиотека");
    lib.addBook(new MainHallBook("1984", "Оруэлл", "Антиутопия", 3));
    lib.addBook(new ReadingRoomBook("Мастер и Маргарита", "Булгаков", "Роман", "Классика"));
    
    // П.8 - вывод после работы
    cout << "\nКниг всего (после создания): " << Book::getTotalCount() << endl;
    cout << "Книг в библиотеках: " << Library::getStoredCount() << endl;
    cout << "\nСодержимое библиотеки:\n";
    lib.displayAll();
    
    return 0;
}