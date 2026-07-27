#include <iostream>
#include <iomanip>
#include <string>

#include "Book.h"
using namespace std;
// the default constructor
Book::Book():
    id(0), title(""), author(""), category(""), available(true) {}

// prametrized constructor
Book::Book(int id,
        const string& title,
        const string& author,
        const string& category,
        bool available):
    
    id(id), title(title), author(author), category(category), available(available) {}

// display
void Book::display() const
{
    cout << left
              << setw(8) << id
              << setw(30)<< title
              << setw(25)<< author
              << setw(20) << category
              << (available ? "Available" : "Borrowed")
              << '\n';
}

int Book::getId() const
{
    return id;
}
const string& Book::getTitle() const
{
    return title;
}
const string& Book::getAuthor() const
{
    return author;
}
const string& Book::getCategory() const
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
