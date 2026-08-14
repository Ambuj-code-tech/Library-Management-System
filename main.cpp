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
        << "12. Display Borrow Records\n"
        << "13. Update Book\n"
        << "14. Update User\n"
        << "15. Exit\n"
        << "Enter your choice: ";
}

int main()
{
    // create library object
    Library lib;

    lib.loadBooks("books.csv");
    lib.loadUsers("users.csv");
    lib.loadBorrowRecords("records.csv");

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

                if (lib.findBookById(id) != nullptr)
                {
                    std::cout << "Book ID already exists. Please use a different ID.\n";
                    break;
                }

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

                if (!lib.saveBooks("books.csv"))
                {
                    std::cout << "Warning: failed to save books to books.csv.\n";
                }

                std::cout << "Book added successfully!\n";

                break;
            }
            case 2: // Remove Book
            {
                int bookId;

                std::cout << "Book Id: ";
                std::cin >> bookId;

                if (lib.removeBook(bookId))
                {
                    lib.saveBooks("books.csv");
                    std::cout << "Book removed successfully.\n";
                }
                else
                {
                    std::cout << "Cannot remove a borrowed book or book not found.\n";
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
                    lib.saveBooks("books.csv");
                    lib.saveUsers("users.csv");
                    lib.saveBorrowRecords("records.csv");
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
                    lib.saveBooks("books.csv");
                    lib.saveUsers("users.csv");
                    lib.saveBorrowRecords("records.csv");
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
                lib.resetBooks();
                lib.resetBorrowRecords();
                lib.saveBooks("books.csv");
                lib.saveBorrowRecords("records.csv");
                std::cout << "Book data reset successfully.\n";
                break;
            }
            case 8:  // Register User
            {
                int userId;
                std::string username;

                std::cout << "User ID: ";
                std::cin >> userId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Username: ";
                std::getline(std::cin, username);

                User newUser(userId, username);

                lib.addUser(newUser);
                lib.saveUsers("users.csv");
                std::cout << "User registered successfully!\n";
                break;
            }
            case 9:  // Remove User
            {
                int userId;

                std::cout << "User Id: ";
                std::cin >> userId;

                if(lib.removeUser(userId))
                {
                    lib.saveUsers("users.csv");
                    std::cout << "User deregistered successfully.\n";
                }
                
                break;
            }
            case 10:  // Display Users
            {
                lib.displayAllUsers();
                break;
            }
            case 11:  // Reset User Data
            {
                lib.resetUsers();
                lib.resetBorrowRecords();
                lib.saveUsers("users.csv");
                lib.saveBorrowRecords("records.csv");
                std::cout << "User data reset successfully.\n";
                break;
            }
            case 12:  // Display Borrow Records
            {
                lib.displayBorrowRecords();
                break;
            }
            case 13: // Update Book
            {
                int bookId;
                std::cout << "Book Id: ";
                std::cin >> bookId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string title;
                std::string author;
                std::string category;

                std::cout << "New Title: ";
                std::getline(std::cin, title);
                std::cout << "New Author: ";
                std::getline(std::cin, author);
                std::cout << "New Category: ";
                std::getline(std::cin, category);

                if (lib.updateBook(bookId, title, author, category))
                {
                    lib.saveBooks("books.csv");
                    std::cout << "Book updated successfully.\n";
                }
                break;
            }
            case 14: // Update User
            {
                int userId;
                std::cout << "User Id: ";
                std::cin >> userId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string username;
                std::cout << "New Username: ";
                std::getline(std::cin, username);

                if (lib.updateUser(userId, username))
                {
                    lib.saveUsers("users.csv");
                    std::cout << "User updated successfully.\n";
                }

                break;
            }
            case 15:  // Exit
            {
                lib.saveBooks("books.csv");
                lib.saveUsers("users.csv");
                lib.saveBorrowRecords("records.csv");
                return 0;
            }
        }
    }
}