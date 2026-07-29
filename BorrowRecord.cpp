#include <chrono>
#include "BorrowRecord.h"

// parametrized constructor
BorrowRecord::BorrowRecord(
    int recordId,
    int userId,
    int bookId,
    const Date& borrowDate,
    const Date& dueDate
):
    recordId(recordId), userId(userId), bookId(bookId), borrowDate(borrowDate), dueDate(dueDate) {}

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

double BorrowRecord::calculateFine(const Date& today, double finePerDay) const
{
    // If the book has already been returned or is not overdue,
    // there is no fine.
    if (returned || !isOverdue(today))
    {
        return 0.0;
    }

    auto overdueDays = SysDays(today) - SysDays(dueDate);

    return overdueDays.count() * (double)finePerDay;
}