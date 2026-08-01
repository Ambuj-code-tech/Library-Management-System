#include <iostream>
#include <iomanip>
#include <string>

#include "Book.h"

// the default constructor
Book::Book():
    id(0), title(""), author(""), category(""), available(true) {}

// prametrized constructor
Book::Book(int id,
        const std::string& title,
        const std::string& author,
        const std::string& category,
        bool available):
    
    id(id), title(title), author(author), category(category), available(available) {}

// display
void Book::display() const
{
    std::cout << std::left
              << std::setw(8)  << id
              << std::setw(30) << title
              << std::setw(25) << author
              << std::setw(20) << category
              << (available ? "Available" : "Borrowed")
              << '\n';
}

int Book::getBookId() const
{
    return id;
}
const std::string& Book::getTitle() const
{
    return title;
}
const std::string& Book::getAuthor() const
{
    return author;
}
const std::string& Book::getCategory() const
{
    return category;
}
bool Book::isAvailable() const
{
    return available;
}

void Book::setAvailability(bool status)
{
    this->available = status;
}