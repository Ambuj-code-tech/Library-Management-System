#include <iostream>
#include <limits>
#include "Library.h"

void displayMenu()
{
    std::cout
        << "========== LIBRARY ==========\n"
        << "1.  Add Book\n"
        << "2.  Remove Book\n"
        << "3.  Search Book\n"
        << "4.  Borrow Book\n"
        << "5.  Return Book\n"
        << "6.  Display Books\n"
        << "7.  Reset Book Data\n"
        << "8.  Register User\n"
        << "9.  Remove User\n"
        << "10. Display Users\n"
        << "11. Reset User Data\n"
        << "12. Exit\n"
        << "Enter your choice: ";
}

int main()
{
    // create library object
    Library lib;

    lib.loadBooks("books.txt");
    lib.loadUsers("users.txt");
    lib.loadBorrowRecords("records.txt");

    while (true)
    {
        // display menu
        displayMenu();

        // read choice
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
            case 1: // Add Book
            {
                int id;
                std::string title;
                std::string author;
                std::string category;

                std::cout << "Book ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Title: ";
                getline(std::cin, title);

                std::cout << "Author: ";
                getline(std::cin, author);

                std::cout << "Category: ";
                getline(std::cin, category);

                // Create a Book object
                Book newBook(id, title, author, category);

                // Add it to the library
                lib.addBook(newBook);

                std::cout << "Book added successfully!\n";

                break;
            }
            case 2: // Remove Book
            {
                int bookId;

                std::cout << "Book Id: ";
                std::cin >> bookId;

                if(!lib.removeBook(bookId))
                {
                    std::cout << "Book Removed Successfully.\n";
                }
                else{
                    std::cout << "Cannot remove a borrowed book.\n";
                }

                break;
            }
            case 3:  // Search Book
            {
                int bookId;

                std::cout << "Book Id: ";
                std::cin >> bookId;

                const Book* book = lib.findBookById(bookId);

                if (book)
                    book->display();
                else
                    std::cout << "Book not found.\n";

                break;
            }
            case 4:  // Borrow Book
            {
                int bookId;
                int userId;

                std::cout << "Book Id: ";
                std::cin >> bookId;

                std::cout << "User Id: ";
                std::cin >> userId;

                if(lib.borrowBook(userId, bookId))
                {
                    std::cout << "Book borrowed successfully!\n";
                }

                break;
            }
            case 5:  // Return Book
            {
                int bookId;
                int userId;

                std::cout << "Book Id: ";
                std::cin >> bookId;

                std::cout << "User Id: ";
                std::cin >> userId;

                if(lib.returnBook(userId, bookId))
                {
                    std::cout << "Book returned successfully!\n";
                }

                break;
            }
            case 6:  // Display Books
            {
                lib.displayAllBooks();
                break;
            }
            case 7:  // Reset Book Data
            {
                //...
            }
            case 8:  // Register User
            {
                int userId;
                std::string username;

                std::cout << "User ID: ";
                std::cin >> userId;

                std::cout << "Username: ";
                std::cin >> username;

                User newUser(userId, username);

                lib.addUser(newUser);
            }
            case 9:  // Remove User
            {
                int userId;

                std::cout << "User Id: ";
                std::cin >> userId;

                if(lib.removeUser(userId))
                    std::cout << "User deregestered successfully.\n";
                
                break;
            }
            case 10:  // Display Users
            {
                lib.displayAllUsers();
                break;
            }
            case 11:  // Reset User Data
            {
                //...
            }
            case 12:  // Exit
            {
                return 0;
            }
        }
    }
}