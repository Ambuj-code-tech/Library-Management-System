#include <chrono>
#include <iostream>
#include <iomanip>
# include <chrono>

#include "BorrowRecord.h"

constexpr int BorrowPeriod = 30;
constexpr int finePerDay = 5;

// parametrized constructor
BorrowRecord::BorrowRecord(
    int recordId,
    int userId,
    int bookId,
    const Date& borrowDate
):
    recordId(recordId),
    userId(userId),
    bookId(bookId),
    borrowDate(borrowDate),
    dueDate(SysDays(borrowDate) + std::chrono::days{BorrowPeriod})
{}

// getters
int BorrowRecord::getRecordId() const
{
    return recordId;
}
int BorrowRecord::getUserId() const
{
    return userId;
}
int BorrowRecord::getBookId() const
{
    return bookId;
}
Date BorrowRecord::getBorrowDate() const
{
    return borrowDate;
}
Date BorrowRecord::getDueDate() const
{
    return dueDate;
}
Date BorrowRecord::getReturnDate() const
{
    return returnDate;
}
bool BorrowRecord::isReturned() const
{
    return returned;
}

// Return book
void BorrowRecord::markReturned(const Date& returnDate)
{
    this->returnDate = returnDate;
    returned = true;
}

// utility
bool BorrowRecord::isOverdue(const Date& today) const
{
    // A returned book cannot be overdue.
    if (returned)
    {
        return false;
    }

    return SysDays(today) > SysDays(dueDate);
}

double BorrowRecord::calculateFine(const Date& today) const
{
    // If the book has already been returned or is not overdue,
    // there is no fine.
    if (returned || !isOverdue(today))
    {
        return 0.0;
    }

    auto overdueDays = SysDays(today) - SysDays(dueDate);

    return overdueDays.count() * finePerDay;
}

void BorrowRecord::display() const
{
    const auto now = std::chrono::system_clock::now();
    const auto current_day = std::chrono::floor<std::chrono::days>(now);
    const Date today{current_day};

    const double fine = calculateFine(today);

    std::cout << std::left
              << std::setw(10) << recordId
              << std::setw(10) << userId
              << std::setw(10) << bookId;

    std::cout << std::right << std::setfill('0');

    std::cout << std::setw(4) << static_cast<int>(borrowDate.year()) << '-'
              << std::setw(2) << static_cast<unsigned>(borrowDate.month()) << '-'
              << std::setw(2) << static_cast<unsigned>(borrowDate.day()) << "    ";

    std::cout << std::setw(4) << static_cast<int>(dueDate.year()) << '-'
              << std::setw(2) << static_cast<unsigned>(dueDate.month()) << '-'
              << std::setw(2) << static_cast<unsigned>(dueDate.day());

    std::cout << std::left << std::setfill(' ')
              << "    "
              << std::fixed << std::setprecision(2)
              << std::setw(10) << fine
              << '\n';
}