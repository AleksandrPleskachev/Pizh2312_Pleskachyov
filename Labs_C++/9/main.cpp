#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Базовый класс (из предыдущих работ)
class Book {
protected:
    string title;
    string author;
    string genre;
public:
    Book(string t = "", string a = "", string g = "") 
        : title(t), author(a), genre(g) {}
    
    virtual ~Book() {}

    // П.2: Глобальный оператор вывода (дружественная функция)
    friend ostream& operator<<(ostream& os, const Book& book) {
        book.display(os);
        return os;
    }
    
    // П.3: Глобальный оператор ввода
    friend istream& operator>>(istream& is, Book& book) {
        cout << "Введите название: ";
        getline(is, book.title);
        cout << "Введите автора: ";
        getline(is, book.author);
        cout << "Введите жанр: ";
        getline(is, book.genre);
        return is;
    }
    
    virtual void display(ostream& os) const {
        os << title << " | " << author << " | " << genre;
    }
    
    // Для сериализации
    virtual void save(ofstream& out) const {
        out << title << '\n' << author << '\n' << genre << '\n';
    }
    
    virtual void load(ifstream& in) {
        getline(in, title);
        getline(in, author);
        getline(in, genre);
    }
};

// Класс-наследник (пример)
class Novel : public Book {
    int pages;
public:
    Novel(string t = "", string a = "", string g = "", int p = 0) 
        : Book(t, a, g), pages(p) {}
    
    void display(ostream& os) const override {
        Book::display(os);
        os << " | Страниц: " << pages;
    }
    
    void save(ofstream& out) const override {
        Book::save(out);
        out << pages << '\n';
    }
    
    void load(ifstream& in) override {
        Book::load(in);
        in >> pages;
        in.ignore(); // Пропустить \n
    }
};

// Основной класс (из предыдущих работ)
class Library {
    vector<Book*> books;
public:
    // П.4: Сохранение в файл
    void saveToFile(const string& filename) const {
        ofstream out(filename);
        if (!out) throw runtime_error("Не удалось открыть файл для записи");
        
        out << books.size() << '\n'; // Сохраняем количество книг
        for (const auto& book : books) {
            book->save(out);
        }
    }
    
    // П.5: Чтение из файла
    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) throw runtime_error("Не удалось открыть файл для чтения");
        
        // Очищаем текущие данные
        for (auto& book : books) delete book;
        books.clear();
        
        // Читаем количество книг
        int count;
        in >> count;
        in.ignore();
        
        // Читаем книги (в этом примере только базовый тип)
        for (int i = 0; i < count; ++i) {
            Book* book = new Book();
            book->load(in);
            books.push_back(book);
        }
    }
    
    // Добавление книги
    void addBook(Book* book) {
        books.push_back(book);
    }
    
    // Вывод всех книг
    void displayAll() const {
        for (const auto& book : books) {
            cout << *book << endl;
        }
    }
    
    ~Library() {
        for (auto& book : books) delete book;
    }
};

int main() {
    try {
        Library lib;
        
        // П.2-3: Использование операторов ввода/вывода
        Book book1;
        cin >> book1; // Ввод данных
        cout << "Введенная книга: " << book1 << endl; // Вывод
        
        // Добавляем несколько книг
        lib.addBook(new Book("1984", "Оруэлл", "Антиутопия"));
        lib.addBook(new Novel("Преступление и наказание", "Достоевский", "Роман", 500));
        
        // П.4: Сохранение в файл
        lib.saveToFile("library.txt");
        cout << "Библиотека сохранена в файл\n";
        
        // П.5: Чтение из файла
        Library lib2;
        lib2.loadFromFile("library.txt");
        cout << "\nЗагруженная библиотека:\n";
        lib2.displayAll();
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}