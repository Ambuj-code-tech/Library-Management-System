# 📚 Library Management System

A console-based **Library Management System** developed in C++ using Object-Oriented Programming (OOP), file handling, and date/time management.

The system manages books, users, and borrowing transactions through an interactive command-line interface. It supports complete book and user management, borrowing and returning books, persistent data storage, borrow record tracking, updates, searching, and overdue fine calculation.

---

## 🚀 Features

### 📖 Book Management

- Add new books
- Remove books
- Search for books
- Display all books
- Update book information
- Reset book data
- Track book availability

### 👤 User Management

- Register new users
- Remove users
- Display all registered users
- Update user information
- Reset user data

### 🔄 Borrowing & Returning

- Borrow available books
- Return borrowed books
- Maintain borrowing records
- Display borrowing history
- Track borrow and return dates
- Calculate overdue fines

### 💾 Data Persistence

- Store library data using files
- Load existing data when the program starts
- Save changes during program execution
- Maintain book, user, and borrowing information between program executions

---

## 🖥️ System Menu

```text
========== LIBRARY ==========
1.  Add Book
2.  Remove Book
3.  Search Book
4.  Borrow Book
5.  Return Book
6.  Display Books
7.  Reset Book Data
8.  Register User
9.  Remove User
10. Display Users
11. Reset User Data
12. Display Borrow Records
13. Update Book
14. Update User
15. Exit
```

## 🏗️ Project Structure

```
Library-Management-System/
│
├── Book.h
├── Book.cpp
│
├── User.h
├── User.cpp
│
├── BorrowRecord.h
├── BorrowRecord.cpp
│
├── Date.h
├── Date.cpp
│
├── Library.h
├── Library.cpp
│
├── main.cpp
│
├── books.txt
├── users.txt
├── borrow_records.txt
│
└── README.md
```

## 🧩 Core Components

### Book

The Book class represents a book in the library.

It manages book-related information and operations such as:

```text
Book identification
Title
Author
Availability
Adding books
Removing books
Searching books
Updating book information
Displaying books
```

### User

The User class represents a registered library user.

It manages user-related information and supports:

```text
User registration
User identification
Removing users
Updating user information
Displaying users
```

### BorrowRecord

The BorrowRecord class represents a borrowing transaction between a user and a book.

It keeps track of information such as:

```text
User
Book
Borrow date
Return date
Borrowing status
Overdue information
Fine calculation
```

Borrow records allow the system to maintain a history of library transactions.

---

## ⚙️ How the System Works

```bash
                 ┌─────────────────┐
                 │      START      │
                 └────────┬────────┘
                          │
                          ▼
                ┌────────────────────┐
                │   Load Data        │
                └─────────┬──────────┘
                          │
                          ▼
                ┌────────────────────┐
                │   Display Menu     │
                └─────────┬──────────┘
                          │
                          ▼
              ┌─────────────────────────┐
              │ Select an Operation     │
              └────────────┬────────────┘
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
   Book Management   User Management   Borrowing
          │                │                │
          └────────────────┼────────────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │ Update / Save   │
                  │      Data       │
                  └────────┬────────┘
                           │
                           ▼
                  ┌─────────────────┐
                  │      Exit       │
                  └─────────────────┘
```

## 🛠️ Technologies Used

### Programming Language

- C++

### Libraries / Tools

- C++ Standard Library
- STL
- `chrono` for date/time functionality
- File streams for persistent storage

### Programming Concepts

- Object-Oriented Programming
- Classes and Objects
- Encapsulation
- Constructors
- Member Functions
- Composition
- Modular Program Design
- File Input/Output
- Data Persistence
- Date and Time Handling
- Data Validation
- CRUD Operations
- Transaction Management

---

## ▶️ How to Run

### 1. Clone the Repository
```bash
git clone <repository-url>
```

### 2. Navigate to the Project Directory
``` bash
cd Library-Management-System
```

### 3. Compile the Project
Using g++:
```bash
g++ *.cpp -o library
```

### 4. Run the Program
Windows
```bash
library.exe
```
Linux / macOS
```bash
./library
```
---

## 🎯 Learning Outcomes

This project provided practical experience with:

- Designing classes for real-world entities
- Applying Object-Oriented Programming principles
- Managing relationships between multiple classes
- Working with multiple source and header files
- Reading and writing structured data using files
- Managing persistent application state
- Handling dates and time-based calculations
- Implementing search and update operations
- Designing menu-driven applications
- Managing borrowing transactions and records

---

## 👨‍💻 Author

**Ambuj**\
Electrical Engineering\
IIT Bhubaneswar
---
