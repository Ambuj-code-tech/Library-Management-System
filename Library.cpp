#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>

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

void Library::resetBooks()
{
    books.clear();
}

void Library::resetUsers()
{
    users.clear();
}

void Library::resetBorrowRecords()
{
    borrowRecords.clear();
    nextRecordId = 1;
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
          << std::setw(15) << "Fine"
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
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << ".\n";
        return false;
    }

    books.clear();

    std::string line;
    if (!std::getline(file, line))
    {
        file.close();
        return true;
    }

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string idStr;
        std::string title;
        std::string author;
        std::string category;
        std::string availableStr;

        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, title, ',') ||
            !std::getline(ss, author, ',') ||
            !std::getline(ss, category, ',') ||
            !std::getline(ss, availableStr, ','))
        {
            std::cout << "Invalid book data format in " << filename << ".\n";
            file.close();
            return false;
        }

        try
        {
            int id = std::stoi(idStr);
            bool available = std::stoi(availableStr);
            books.emplace_back(id, title, author, category, available);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid numeric value in " << filename << ".\n";
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool Library::saveBooks(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << " for writing.\n";
        return false;
    }

    file << "id,title,author,category,available\n";

    for (const auto& book : books)
    {
        file << book.getBookId() << ','
             << book.getTitle() << ','
             << book.getAuthor() << ','
             << book.getCategory() << ','
             << (book.isAvailable() ? 1 : 0) << '\n';
    }

    file.close();
    return true;
}

bool Library::loadUsers(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << " .\n";
        return false;
    }

    users.clear();

    std::string line;
    if (!std::getline(file, line))
    {
        file.close();
        return true;
    }

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string strUserId;
        std::string username;
        std::string borrowedBooksField;

        if (!std::getline(ss, strUserId, ',') ||
            !std::getline(ss, username, ',') ||
            !std::getline(ss, borrowedBooksField, ','))
        {
            std::cout << "Invalid user data format in " << filename << " .\n";
            file.close();
            return false;
        }

        try
        {
            int id = std::stoi(strUserId);
            User user(id, username);

            if (!borrowedBooksField.empty())
            {
                std::stringstream borrowedStream(borrowedBooksField);
                std::string bookIdStr;

                while (std::getline(borrowedStream, bookIdStr, ';'))
                {
                    if (!bookIdStr.empty())
                    {
                        user.borrowBook(std::stoi(bookIdStr));
                    }
                }
            }

            users.push_back(user);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid numeric value in " << filename << " .\n";
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool Library::saveUsers(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << " for writing.\n";
        return false;
    }

    file << "id,username,borrowedBooks\n";

    for (const auto& user : users)
    {
        file << user.getUserId() << ',' << user.getUsername() << ',';
        const auto& borrowedBooks = user.getBorrowedBooks();
        for (size_t i = 0; i < borrowedBooks.size(); i++)
        {
            if (i > 0)
            {
                file << ';';
            }
            file << borrowedBooks[i];
        }
        file << '\n';
    }

    file.close();
    return true;
}

bool Library::loadBorrowRecords(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << ".\n";
        return false;
    }

    borrowRecords.clear();
    nextRecordId = 1;

    std::string line;
    if (!std::getline(file, line))
    {
        file.close();
        return true;
    }

    auto parseDate = [](const std::string& str, Date& date) {
        if (str.empty())
            return false;

        int year = 0;
        unsigned month = 0;
        unsigned day = 0;
        char dash1 = '\0';
        char dash2 = '\0';

        std::stringstream ss(str);
        if (!(ss >> year >> dash1 >> month >> dash2 >> day))
            return false;

        if (dash1 != '-' || dash2 != '-')
            return false;

        date = Date{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
        return true;
    };

    int maxRecordId = 0;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string recordIdStr;
        std::string userIdStr;
        std::string bookIdStr;
        std::string borrowDateStr;
        std::string returnedStr;
        std::string returnDateStr;

        if (!std::getline(ss, recordIdStr, ',') ||
            !std::getline(ss, userIdStr, ',') ||
            !std::getline(ss, bookIdStr, ',') ||
            !std::getline(ss, borrowDateStr, ',') ||
            !std::getline(ss, returnedStr, ','))
        {
            std::cout << "Invalid borrow record data format in " << filename << ".\n";
            file.close();
            return false;
        }

        try
        {
            int recordId = std::stoi(recordIdStr);
            int userId = std::stoi(userIdStr);
            int bookId = std::stoi(bookIdStr);
            bool returned = std::stoi(returnedStr) != 0;

            Date borrowDate;
            if (!parseDate(borrowDateStr, borrowDate))
            {
                std::cout << "Invalid borrow date in " << filename << ".\n";
                file.close();
                return false;
            }

            BorrowRecord record(recordId, userId, bookId, borrowDate);
            if (returned && std::getline(ss, returnDateStr, ','))
            {
                Date returnDate;
                if (parseDate(returnDateStr, returnDate))
                {
                    record.markReturned(returnDate);
                }
            }

            borrowRecords.push_back(record);
            maxRecordId = std::max(maxRecordId, recordId);
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid numeric value in " << filename << ".\n";
            file.close();
            return false;
        }
    }

    file.close();
    nextRecordId = maxRecordId + 1;
    return true;
}

bool Library::updateBook(int bookId, const std::string& title, const std::string& author, const std::string& category)
{
    Book* book = findBookById(bookId);
    if (book == nullptr)
    {
        std::cout << "Book not found.\n";
        return false;
    }

    book->setTitle(title);
    book->setAuthor(author);
    book->setCategory(category);
    return true;
}

bool Library::updateUser(int userId, const std::string& username)
{
    User* user = findUserById(userId);
    if (user == nullptr)
    {
        std::cout << "User not found.\n";
        return false;
    }

    user->setUsername(username);
    return true;
}

bool Library::saveBorrowRecords(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open " << filename << " for writing.\n";
        return false;
    }

    file << "recordId,userId,bookId,borrowDate,returned,returnDate\n";

    auto formatDate = [](const Date& date) {
        std::stringstream ss;
        ss << std::setfill('0')
           << std::setw(4) << static_cast<int>(date.year()) << '-'
           << std::setw(2) << static_cast<unsigned>(date.month()) << '-'
           << std::setw(2) << static_cast<unsigned>(date.day());
        return ss.str();
    };

    for (const auto& record : borrowRecords)
    {
        file << record.getRecordId() << ','
             << record.getUserId() << ','
             << record.getBookId() << ','
             << formatDate(record.getBorrowDate()) << ','
             << (record.isReturned() ? 1 : 0) << ',';

        if (record.isReturned())
        {
            file << formatDate(record.getReturnDate());
        }

        file << '\n';
    }

    file.close();
    return true;
}
