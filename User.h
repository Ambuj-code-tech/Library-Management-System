#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User
{
private:
    int userId;
    std::string username;
    std::vector<int> borrowedBooksId;

public:
    User();
    User(int id, const std::string& username);

    int getUserId() const;
    const std::string& getUsername() const;
    const std::vector<int>& getBorrowedBooks() const;

    void borrowBook(int bookId);
    void returnBook(int bookId);
    void clearBorrowedBooks();

    void display() const;
};

#endif