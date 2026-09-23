#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Book {
public:
    string ISBN;
    string title;
    string author;
    string category;
    bool isAvailable;

    Book() : isAvailable(true) {}
    Book(string isbn, string t, string a, string c, bool avail)
        : ISBN(isbn), title(t), author(a), category(c), isAvailable(avail) {}

    string toCSV() const {
        return ISBN + "," + title + "," + author + "," + category + "," + (isAvailable ? "1" : "0");
    }

    static Book fromCSV(const string& line) {
        Book b;
        stringstream ss(line);
        string availStr;
        getline(ss, b.ISBN, ',');
        getline(ss, b.title, ',');
        getline(ss, b.author, ',');
        getline(ss, b.category, ',');
        getline(ss, availStr);
        b.isAvailable = (availStr == "1");
        return b;
    }

    void display() const {
        cout << "ISBN: " << ISBN << " | Title: " << title << " | Author: " << author 
             << " | Category: " << category << " | Status: " << (isAvailable ? "Available" : "Issued") << endl;
    }
};

class LibrarySystem {
private:
    string filename;

    vector<Book> loadBooks() const {
        vector<Book> books;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (!line.empty()) {
                    books.push_back(Book::fromCSV(line));
                }
            }
            file.close();
        }
        return books;
    }

    void saveBooks(const vector<Book>& books) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.toCSV() << "\n";
            }
            file.close();
        } else {
            cerr << "Error opening file for writing." << endl;
        }
    }

public:
    LibrarySystem(string dbFilename) : filename(dbFilename) {}

    void addBook(const Book& book) {
        vector<Book> books = loadBooks();
        books.push_back(book);
        saveBooks(books);
        cout << "Book added successfully!" << endl;
    }

    void searchBook(const string& title) const {
        vector<Book> books = loadBooks();
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(title) != string::npos) {
                book.display();
                found = true;
            }
        }
        if (!found) cout << "No book found with title containing: " << title << endl;
    }

    void issueBook(const string& isbn) {
        vector<Book> books = loadBooks();
        bool found = false;
        for (auto& book : books) {
            if (book.ISBN == isbn) {
                found = true;
                if (book.isAvailable) {
                    book.isAvailable = false;
                    saveBooks(books);
                    cout << "Book issued successfully." << endl;
                } else {
                    cout << "Book is already issued." << endl;
                }
                break;
            }
        }
        if (!found) cout << "Book not found." << endl;
    }

    void returnBook(const string& isbn) {
        vector<Book> books = loadBooks();
        bool found = false;
        for (auto& book : books) {
            if (book.ISBN == isbn) {
                found = true;
                if (!book.isAvailable) {
                    book.isAvailable = true;
                    saveBooks(books);
                    cout << "Book returned successfully." << endl;
                } else {
                    cout << "Book was not issued." << endl;
                }
                break;
            }
        }
        if (!found) cout << "Book not found." << endl;
    }

    void generateAvailabilityReport() const {
        vector<Book> books = loadBooks();
        cout << "\n=== Library Availability Report ===" << endl;
        int availCount = 0;
        int issuedCount = 0;
        for (const auto& book : books) {
            book.display();
            if (book.isAvailable) availCount++;
            else issuedCount++;
        }
        cout << "-----------------------------------" << endl;
        cout << "Total Books: " << books.size() << " | Available: " << availCount << " | Issued: " << issuedCount << endl;
        cout << "===================================\n" << endl;
    }
};

int main() {
    LibrarySystem lib("library_db.txt");
    
    // Clear old data for demonstration
    ofstream clearFile("library_db.txt", ios::trunc);
    clearFile.close();

    cout << "Adding books to the library..." << endl;
    lib.addBook(Book("978-0131103627", "The C Programming Language", "Brian Kernighan", "Programming", true));
    lib.addBook(Book("978-0201616224", "The Pragmatic Programmer", "Andy Hunt", "Software Engineering", true));
    lib.addBook(Book("978-0321563842", "The C++ Programming Language", "Bjarne Stroustrup", "Programming", true));

    lib.generateAvailabilityReport();

    cout << "\nIssuing book 978-0201616224..." << endl;
    lib.issueBook("978-0201616224");

    cout << "\nSearching for 'C++'..." << endl;
    lib.searchBook("C++");

    lib.generateAvailabilityReport();

    cout << "\nReturning book 978-0201616224..." << endl;
    lib.returnBook("978-0201616224");
    
    lib.generateAvailabilityReport();

    return 0;
}
