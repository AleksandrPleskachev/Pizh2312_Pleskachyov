#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Базовый класс (сохранены все предыдущие свойства)
class Book {
protected:
    string title;
    string author;
    string genre;
    static int totalCount; // Счетчик из ЛР5
public:
    // Конструкторы (из ЛР3-5)
    Book(string t, string a, string g) : title(t), author(a), genre(g) { ++totalCount; }
    virtual ~Book() { --totalCount; }
    
    // Методы из предыдущих работ
    virtual void display() const = 0;
    static int getTotalCount() { return totalCount; } // Из ЛР5
    
    // Для оператора <<
    friend ostream& operator<<(ostream& os, const Book& book) {
        book.display();
        return os;
    }
};
int Book::totalCount = 0;

// Класс-наследник 1 (сохранен весь функционал)
class MainHallBook : public Book {
    int shelf;
public:
    MainHallBook(string t, string a, string g, int s) : Book(t, a, g), shelf(s) {}
    MainHallBook() : Book("", "", ""), shelf(0) {} // Для оператора ++
    
    void display() const override {
        cout << "[Основной зал] " << title << " | " << author 
             << " | " << genre << " | Полка: " << shelf << endl;
    }
};

// Класс-наследник 2 (сохранен весь функционал)
class ReadingRoomBook : public Book {
    string section;
public:
    ReadingRoomBook(string t, string a, string g, string s) : Book(t, a, g), section(s) {}
    ReadingRoomBook() : Book("", "", ""), section("") {} // Для оператора ++
    
    void display() const override {
        cout << "[Читальный зал] " << title << " | " << author 
             << " | " << genre << " | Раздел: " << section << endl;
    }
};

// Основной класс (добавлены операторы + сохранив предыдущий функционал)
class Library {
    vector<Book*> books;
    static int storedCount; // Из ЛР5
public:
    // Сохраненные методы из ЛР1-5
    void addBook(Book* book) { books.push_back(book); ++storedCount; }
    static int getStoredCount() { return storedCount; }
    ~Library() { 
        storedCount -= books.size(); 
        for(auto b : books) delete b; 
    }
    
    // П.2: Оператор + для добавления наследника
    Library& operator+(MainHallBook* book) {
        books.push_back(book);
        ++storedCount;
        return *this;
    }
    
    // П.3: Префиксный ++
    Library& operator++() {
        books.push_back(new MainHallBook());
        ++storedCount;
        return *this;
    }
    
    // П.3: Постфиксный ++
    Library operator++(int) {
        Library temp = *this;
        books.push_back(new ReadingRoomBook());
        ++storedCount;
        return temp;
    }
    
    // П.4: Оператор []
    Book* operator[](size_t index) {
        if(index >= books.size()) throw out_of_range("Неверный индекс");
        return books[index];
    }
    
    // П.5: Оператор <<
    friend ostream& operator<<(ostream& os, const Library& lib) {
        for(const auto& book : lib.books) {
            book->display();
        }
        return os;
    }
};
int Library::storedCount = 0;

int main() {
    // П.6: Демонстрация всех операторов
    
    Library lib;
    
    // П.2: Оператор +
    lib + new MainHallBook("1984", "Оруэлл", "Антиутопия", 3);
    
    // П.3: Операторы ++
    ++lib; // Префиксный
    lib++; // Постфиксный
    
    // П.4: Оператор []
    cout << "Книга 0:\n" << *lib[0] << endl;
    
    // П.5: Оператор <<
    cout << "\nВсе книги:\n" << lib;
    
    // Проверка сохранения старого функционала
    cout << "\nВсего книг в системе: " << Book::getTotalCount() << endl;
    cout << "Книг в библиотеке: " << Library::getStoredCount() << endl;
    
    return 0;
}