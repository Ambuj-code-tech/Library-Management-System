#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "User.h"

// the default constructor
User::User(): userId(0), username("none"), borrowedBooksId() {}

// parameterized constructor
User::User(int userId, const std::string& username):
    userId(userId), username(username), borrowedBooksId() {}

// getter functions
int User::getId() const
{
    return userId;
}
const std::string& User::getUsername() const
{
    return username;
}
const std::vector<int>& User::getBorrowedBooks() const
{
    return borrowedBooksId;
}

// setter functions
void User::borrowBook(int bookId)
{
    borrowedBooksId.push_back(bookId);
}
void User::returnBook(int bookId)
{
    auto it = std::find(
        borrowedBooksId.begin(),
        borrowedBooksId.end(),
        bookId
    );

    if (it == borrowedBooksId.end())
    {
        std::cout << "Book ID not found in borrowed books.\n";
        return;
    }

    borrowedBooksId.erase(it);
}

// display
void User::display() const
{
    std::cout << std::left
              << std::setw(18) << "User ID:" << userId << '\n'
              << std::setw(18) << "Username:" << username << '\n'
              << std::setw(18) << "Borrowed Books:";

    if (borrowedBooksId.empty())
    {
        std::cout << "None\n";
        return;
    }

    for (int i = 0, n = borrowedBooksId.size(); i < n; i++)
    {
        std::cout << borrowedBooksId[i];
        if (i < n-1)
        {
            std::cout << ', ';
        }
    }
}