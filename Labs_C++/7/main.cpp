#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Book {
protected:
    string title;
    string author;
    string genre;
public:
    Book(string t, string a, string g) : title(t), author(a), genre(g) {}
    virtual ~Book() {}

    bool operator<(const Book& other) const {
        return title < other.title;
    }

    virtual void display() const = 0;
    
    friend ostream& operator<<(ostream& os, const Book& b) {
        b.display();
        return os;
    }
};

class MainHallBook : public Book {
    int shelf;
public:
    MainHallBook(string t, string a, string g, int s) 
        : Book(t, a, g), shelf(s) {}
        
    void display() const override {
        cout << "[Main] " << title << " by " << author << endl;
    }
};

class ReadingRoomBook : public Book {
    string section;
public:
    ReadingRoomBook(string t, string a, string g, string s) 
        : Book(t, a, g), section(s) {}
        
    void display() const override {
        cout << "[Reading] " << title << " in " << section << endl;
    }
};

template <typename T>
class MyArray {
    vector<T> elements;
public:
    MyArray(size_t n) { elements.reserve(n); }
    
    void add(const T& item) { elements.push_back(item); }
    
    T& get(size_t index) { 
        if(index >= elements.size()) throw out_of_range("Index error");
        return elements[index];
    }
    
    const T& min() const {
        if(elements.empty()) throw runtime_error("Empty array");
        return *min_element(elements.begin(), elements.end());
    }
    
    const T& max() const {
        if(elements.empty()) throw runtime_error("Empty array");
        return *max_element(elements.begin(), elements.end());
    }
    
    size_t size() const { return elements.size(); }
};

int main() {
    // Тестирование с int
    MyArray<int> intArr(3);
    intArr.add(10);
    intArr.add(5);
    intArr.add(20);
    cout << "Int min: " << intArr.min() << endl;
    cout << "Int max: " << intArr.max() << endl;

    // Тестирование с книгами
    MyArray<Book*> bookArr(3);
    bookArr.add(new MainHallBook("1984", "Orwell", "Dystopia", 1));
    bookArr.add(new ReadingRoomBook("Foundation", "Asimov", "SF", "Sci-Fi"));
    bookArr.add(new MainHallBook("Animal Farm", "Orwell", "Satire", 2));
    
    cout << "\nBook with min title:\n" << *bookArr.min() << endl;
    cout << "Book with max title:\n" << *bookArr.max() << endl;

    // Очистка памяти
    for(size_t i = 0; i < bookArr.size(); ++i) {
        delete bookArr.get(i);
    }

    return 0;
}