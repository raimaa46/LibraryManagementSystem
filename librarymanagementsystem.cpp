#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Book {
    string title;
    string author;
    string isbn;
    
public:
    void addBook();
    bool isBookExists(const string& isbn);
    void searchBook();
    void issueBook();
    void returnBook();
    void displayBooks();
};

bool Book::isBookExists(const string& isbn) {
    ifstream file("books.txt");
    string line;
    
    if (!file.is_open()) {
        cout << "Error opening file...\n";
        return false;
    }

    while (getline(file, line)) {
        if (line.find(isbn) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void Book::addBook() {
    cout << "Enter the Title of the book: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter the Author of the book: ";
    getline(cin, author);
    cout << "Enter the ISBN of the book: ";
    cin >> isbn;

    if (isBookExists(isbn)) {
        cout << "Book with this ISBN already exists.\n";
    } else {
        ofstream file("books.txt", ios::app);
        if (file.is_open()) {
            file << isbn << " " << title << " " << author << endl;
            cout << "Book added successfully.\n";
        } else {
            cout << "Error opening file to add book.\n";
        }
    }
}

void Book::searchBook() {
    cout << "Enter ISBN to search: ";
    cin >> isbn;

    ifstream file("books.txt");
    string line;
    
    bool found = false;
    while (getline(file, line)) {
        if (line.find(isbn) != string::npos) {
            cout << "Book found: " << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book with ISBN " << isbn << " not found.\n";
    }
    file.close();
}

void Book::issueBook() {
    cout << "Enter ISBN of the book to issue: ";
    cin >> isbn;
    
    ifstream file("books.txt");
    ofstream issuedFile("issued_books.txt", ios::app);
    ofstream tempFile("temp_books.txt"); 
    string line;

    bool found = false;
    while (getline(file, line)) {
        if (line.find(isbn) != string::npos) {
            issuedFile << line << endl;
            found = true;
            cout << "Book issued successfully: " << line << endl;
        } else {
            tempFile << line << endl;
        }
    }

    if (!found) {
        cout << "Book with ISBN " << isbn << " not found.\n";
    }

    file.close();
    issuedFile.close();
    tempFile.close();
    remove("books.txt");
    rename("temp_books.txt", "books.txt");
}

void Book::returnBook() {
    cout << "Enter ISBN of the book to return: ";
    cin >> isbn;

    ifstream issuedFile("issued_books.txt");
    ofstream tempIssuedFile("temp_issued_books.txt");
    ofstream booksFile("books.txt", ios::app);
    string line;
    bool found = false;

    while (getline(issuedFile, line)) {
        if (line.find(isbn) != string::npos) {
            booksFile << line << endl; 
            found = true;
            cout << "Book returned successfully: " << line << endl;
        } else {
            tempIssuedFile << line << endl;
        }
    }

    if (!found) {
        cout << "No issued book found with ISBN " << isbn << endl;
    }

    issuedFile.close();
    tempIssuedFile.close();
    booksFile.close();

    remove("issued_books.txt");
    rename("temp_issued_books.txt", "issued_books.txt");

}
void Book::displayBooks() {
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "Error opening file...\n";
        return;
    }

    string line;
    cout << "\nThe info of the book is: \n" << endl;
    cout << "ISBN--Book Name--Author Name\n";
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

int main() {
    Book b;
    int choice;

    do {
        cout << "\n------------------------\n";
        cout << "1. Add a book\n";
        cout << "2. Display all books\n";
        cout << "3. Issue a book\n";
        cout << "4. Return a book\n";
        cout << "5. Search for a book\n";
        cout << "6. Exit\n";
        cout << "------------------------\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.addBook();
                break;
            case 2:
                b.displayBooks();
                break;
            case 3:
                b.issueBook();
                break;
            case 4:
                b.returnBook();
                break;
            case 5:
                b.searchBook();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
