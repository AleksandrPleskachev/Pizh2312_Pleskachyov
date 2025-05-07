#include <iostream>
#include <string>
using namespace std;

// Базовый класс Книга
class Book {
protected:
    string title;
    string author;
    string genre;
public:
    // Конструкторы
    Book() : title(""), author(""), genre("") {
        cout << "Конструктор Book()" << endl;
    }
    
    Book(string t, string a, string g) : title(t), author(a), genre(g) {
        cout << "Конструктор Book(string, string, string)" << endl;
    }
    
    // Деструктор
    ~Book() {
        cout << "Деструктор ~Book()" << endl;
    }
    
    // Метод вывода
    void display() {
        cout << title << " | " << author << " | " << genre;
    }
};

// Класс для основного зала
class MainHallBook : public Book {
private:
    int shelf;
public:
    MainHallBook(string t, string a, string g, int s) : Book(t, a, g), shelf(s) {
        cout << "Конструктор MainHallBook()" << endl;
    }
    
    ~MainHallBook() {
        cout << "Деструктор ~MainHallBook()" << endl;
    }
    
    void display() {
        Book::display();
        cout << " | Полка: " << shelf << endl;
    }
};

// Класс для читального зала
class ReadingRoomBook : public Book {
private:
    string section;
public:
    ReadingRoomBook(string t, string a, string g, string s) : Book(t, a, g), section(s) {
        cout << "Конструктор ReadingRoomBook()" << endl;
    }
    
    ~ReadingRoomBook() {
        cout << "Деструктор ~ReadingRoomBook()" << endl;
    }
    
    void display() {
        Book::display();
        cout << " | Раздел: " << section << endl;
    }
};

int main() {
    // 1. Создаем объекты
    Book b1("Война и мир", "Толстой", "Роман");
    MainHallBook m1("1984", "Оруэлл", "Антиутопия", 5);
    ReadingRoomBook r1("Мастер и Маргарита", "Булгаков", "Роман", "Классика");

    // 2. Выводим их
    b1.display();
    m1.display();
    r1.display();

    // 3. Массив базового типа
    Book* arr1[3] = {
        new Book("Книга1", "Автор1", "Жанр1"),
        new MainHallBook("Книга2", "Автор2", "Жанр2", 3),
        new ReadingRoomBook("Книга3", "Автор3", "Жанр3", "Раздел1")
    };

    // 4. Выводим массив
    for(int i = 0; i < 3; i++) {
        arr1[i]->display();
        delete arr1[i];
    }

    // 5. Массив наследника
    MainHallBook arr2[2] = {
        MainHallBook("Книга4", "Автор4", "Жанр4", 1),
        MainHallBook("Книга5", "Автор5", "Жанр5", 2)
    };

    // 6. Выводим массив
    for(int i = 0; i < 2; i++) {
        arr2[i].display();
    }

    return 0;
}