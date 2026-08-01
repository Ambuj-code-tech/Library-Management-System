#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <chrono>
using Date = std::chrono::year_month_day;
using SysDays = std::chrono::sys_days;

class BorrowRecord
{
private:
    int recordId = 0;
    int userId = 0;
    int bookId = 0;

    Date borrowDate;
    Date dueDate;
    Date returnDate;

    bool returned = false;

public:
    // constructors
    BorrowRecord() = default;

    BorrowRecord(
        int recordId,
        int userId,
        int bookId,
        const Date& borrowDate
    );

    // getters
    int getRecordId() const;
    int getUserId() const;
    int getBookId() const;

    Date getBorrowDate() const;
    Date getDueDate() const;
    Date getReturnDate() const;

    bool isReturned() const;

    // Return book
    void markReturned(const Date& returnDate);

    // utility
    bool isOverdue(const Date& today) const;

    double calculateFine(
        const Date& today,
        double finePerDay
    ) const;

    void display() const;
};

#endif