#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

#include "Book.h"
#include "BorrowRecord.h"
#include "User.h"

class Library
{
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::vector<BorrowRecord> borrowRecords;

    int nextRecordId;

public:
    Library();

    // Book operations
    void addBook(const Book& book);
    bool removeBook(int bookId);

    Book* findBookById(int bookId);
    const Book* findBookById(int bookId) const;

    void displayAllBooks() const;

    // User operations
    void addUser(const User& user);
    bool removeUser(int userId);

    User* findUserById(int userId);
    const User* findUserById(int userId) const;

    void displayAllUsers() const;

    // Borrowing
    bool borrowBook(int userId, int bookId);
    bool returnBook(int userId, int bookId);

    // Borrow records
    void displayBorrowRecords() const;

    // File handling
    bool loadBooks(const std::string& filename);
    bool saveBooks(const std::string& filename) const;

    bool loadUsers(const std::string& filename);
    bool saveUsers(const std::string& filename) const;

    bool loadBorrowRecords(const std::string& filename);
    bool saveBorrowRecords(const std::string& filename) const;
};

#endif