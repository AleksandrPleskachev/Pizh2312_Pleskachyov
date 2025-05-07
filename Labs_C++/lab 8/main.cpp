#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <exception>
using namespace std;

// П.5: Пользовательские классы исключений
class BookError : public std::runtime_error {
public:
    BookError(const string& msg) : runtime_error(msg) {}
};

class LibraryError : public std::logic_error {
public:
    LibraryError(const string& msg) : logic_error(msg) {}
};

class Book {
protected:
    string title;
    string author;
public:
    Book(string t, string a) : title(t), author(a) {
        if(title.empty()) throw BookError("Empty title"); // П.2, П.5
    }
    
    virtual void display() const {
        cout << title << " by " << author << endl;
    }
};

class Library {
    vector<Book*> books;
public:
    void addBook(Book* b) {
        if(!b) throw invalid_argument("Null book pointer"); // П.4
        if(books.size() >= 5) throw length_error("Library full"); // П.4
        books.push_back(b);
    }
    
    Book& getBook(size_t index) {
        if(index >= books.size()) throw out_of_range("Invalid index"); // П.4
        return *books[index];
    }
    
    ~Library() {
        for(auto b : books) delete b;
    }
};

void testNestedExceptions() {
    try {
        Library lib;
        lib.addBook(new Book("1984", "Orwell"));
        lib.addBook(nullptr); // Генерирует invalid_argument
    }
    catch(const exception& e) { // П.3, П.4
        cerr << "Caught in testNestedExceptions: " << e.what() << endl;
        throw; // П.6 - передаем наверх
    }
}

void testLocalHandling() {
    try {
        Book b("", "Author"); // Генерирует BookError
    }
    catch(...) { // П.3 - локальная обработка
        cout << "Local handler: caught unknown exception" << endl; // П.7
    }
}

int main() {
    // П.2: Обработка разных типов исключений
    try {
        testNestedExceptions(); // П.6
        
        // Генерируем исключения разных типов:
        throw 42; // int
        throw string("Something went wrong"); // string
        throw LibraryError("Custom library error"); // П.5
        
    } 
    catch(int e) { // П.2
        cerr << "Caught int: " << e << endl;
    }
    catch(const string& e) { // П.2
        cerr << "Caught string: " << e << endl;
    }
    catch(const BookError& e) { // П.5
        cerr << "Book error: " << e.what() << endl;
    }
    catch(const LibraryError& e) { // П.5
        cerr << "Library error: " << e.what() << endl;
    }
    catch(const invalid_argument& e) { // П.4
        cerr << "Invalid argument: " << e.what() << endl;
    }
    catch(const out_of_range& e) { // П.4
        cerr << "Out of range: " << e.what() << endl;
    }
    catch(const exception& e) { // П.4
        cerr << "Standard exception: " << e.what() << endl;
    }
    catch(...) { // П.3
        cerr << "Unknown exception caught!" << endl;
    }
    
    testLocalHandling(); // П.7
    
    return 0;
}