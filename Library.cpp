#include <iostream>
#include <iomanip>

#include "Library.h"

Library::Library(): nextRecordId(1) {}

// Book operations
void Library::addBook(const Book& book)
{
    books.push_back(book);
}

bool Library::removeBook(int bookId)
{
    for (auto it = books.begin(); it != books.end(); it++)
    {
        if (it->getBookId() == bookId)
        {
            if (!(it->isAvailable()))
            {
                return false;
            }

            books.erase(it);
            return true;
        }
    }

    return false;
}

Book* Library::findBookById(int bookId)
{
    for (auto& book : books)
    {
        if (book.getBookId() == bookId)
            return &book;
    }

    return nullptr;
}

const Book* Library::findBookById(int bookId) const
{
    for (const auto& book : books)
    {
        if (book.getBookId() == bookId)
            return &book;
    }

    return nullptr;
}

void Library::displayAllBooks() const
{
    if (books.empty())
    {
        std::cout << "No books available.\n";
        return;
    }

    // header
    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(30) << "Title"
              << std::setw(25) << "Author"
              << std::setw(20) << "Category"
              << "Status\n";

    std::cout << std::string(95, '-') << '\n';

    // content
    for (const auto& book : books)
    {
        book.display();
    }
}

// User operations
void Library::addUser(const User& user)
{
    users.push_back(user);
}

bool Library::removeUser(int userId)
{
    for (auto it = users.begin(); it != users.end(); it++)
    {
        if (it->getUserId() == userId)
        {
            if (!it->getBorrowedBooks().empty())
            {
                std::cout << "User has borrowed books.\n";
                return false;
            }
            
            users.erase(it);
            return true;
        }
    }

    std::cout << "User not regestered.\n";
    return false;
}

User* Library::findUserById(int userId)
{
    for (auto& user : users)
    {
        if (user.getUserId() == userId)
            return &user;
    }

    return nullptr;
}

const User* Library::findUserById(int userId) const
{
    for (const auto& user : users)
    {
        if (user.getUserId() == userId)
            return &user;
    }

    return nullptr;
}

void Library::displayAllUsers() const
{
    if (users.empty())
    {
        std::cout << "No users registered.\n";
        return;
    }

    int sl = 1;

    for (const auto& user : users)
    {
        std::cout << sl++ << '\n';
        user.display();
    }
}

// Borrowing
bool Library::borrowBook(int userId, int bookId)
{
    // Find the user
    User* user = findUserById(userId);
    if (user == nullptr)
    {
        std::cout << "User not found.\n";
        return false;
    }

    // Find the book
    Book* book = findBookById(bookId);
    if (book == nullptr)
    {
        std::cout << "Book not found.\n";
        return false;
    }

    // Check availability
    if (!book->isAvailable())
    {
        std::cout << "Book not available.\n";
        return false;
    }

    // Mark book as borrowed
    book->setAvailability(false);

    // Add book to user's borrowed list
    user->borrowBook(bookId);

    // 1. Get the current system time point
    const auto now = std::chrono::system_clock::now();

    // 2. Cast/floor the time point to days resolution
    const auto current_day = std::chrono::floor<std::chrono::days>(now);

    // 3. Automatically parse into a structured year-month-day object
    const std::chrono::year_month_day today{current_day};

    // Create a borrow record
    BorrowRecord record(
        nextRecordId++,
        userId,
        bookId,
        today
    );

    borrowRecords.push_back(record);

    return true;
}

bool Library::returnBook(int userId, int bookId)
{
    // Find the user
    User* user = findUserById(userId);
    if (user == nullptr)
    {
        std::cout << "User not found.\n";
        return false;
    }

    // Find the book
    Book* book = findBookById(bookId);
    if (book == nullptr)
    {
        std::cout << "Book not found.\n";
        return false;
    }

    // Mark book as available
    book->setAvailability(true);

    // Remove book to user's borrowed list
    user->returnBook(bookId);

    // 1. Get the current system time point
    const auto now = std::chrono::system_clock::now();

    // 2. Cast/floor the time point to days resolution
    const auto current_day = std::chrono::floor<std::chrono::days>(now);

    // 3. Automatically parse into a structured year-month-day object
    const std::chrono::year_month_day today{current_day};

    // Find the matching active borrow record and mark it as returned
    BorrowRecord* record = nullptr;
    for (auto& existingRecord : borrowRecords)
    {
        if (existingRecord.getUserId() == userId &&
            existingRecord.getBookId() == bookId &&
            !existingRecord.isReturned())
        {
            record = &existingRecord;
            break;
        }
    }

    if (record == nullptr)
    {
        std::cout << "No active borrow record found.\n";
        return false;
    }

    record->markReturned(today);
    return true;
}

// Borrow records
void Library::displayBorrowRecords() const
{
    if (borrowRecords.empty())
    {
        std::cout << "No borrow records available.\n";
        return;
    }

    // header
    std::cout << std::left
          << std::setw(10) << "Record ID"
          << std::setw(10) << "User ID"
          << std::setw(10) << "Book ID"
          << std::setw(15) << "Borrow Date"
          << std::setw(15) << "Due Date"
          << '\n';

    std::cout << std::string(60, '-') << '\n';

    // content
    for (const auto& record : borrowRecords)
    {
        record.display();
    }
}

// File handling
bool Library::loadBooks(const std::string& filename)
{
    return false;
}

bool Library::saveBooks(const std::string&) const
{
    return false;
}

bool Library::loadUsers(const std::string&)
{
    return false;
}

bool Library::saveUsers(const std::string&) const
{
    return false;
}

bool Library::loadBorrowRecords(const std::string&)
{
    return false;
}

bool Library::saveBorrowRecords(const std::string&) const
{
    return false;
}