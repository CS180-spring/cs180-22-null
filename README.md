[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10849768&assignment_repo_type=AssignmentRepo)
# Project-CS180-NULL 
## Team Members: 
* Kevin Lin
* Henry Pham
* Cole Shirakata
* Chun Ho Wong
* Irene Wu
# Interface Documentation
## Overview
NullDB is a powerful database solution designed to handle basic text documents with ease. Our innovative platform provides a simple and intuitive way to store and manage text-based data, offering unparalleled performance and reliability.
## Features
* Developers have encrypted access to database (log-in), a manager has more options within the interface
* Developers can insert/delete/update data
* Developers have the option to search for term frequency
* Developers can display records in a table format
## Technology
* C++
* Interface: website


# Text-based Database Program

This is a simple text-based database program built with C++. It supports the following features:

- Basic insert, delete, and update functionality.
- Automatic ID generation for new records.
- Timestamping of records with the current date and time.
- User authentication with username and password, and user-specific record access.
- Root manager account for creating new user accounts.
- Basic filtering and keyword search for records.
- Data persistence through storing records in a text file.
- Future enhancements include encryption and web frontend support.

## Getting Started

To run the program, simply compile the `main.cpp` file using a C++ compiler of your choice. You can then run the compiled executable to start the program.

## Usage

Upon running the program, you will be presented with a menu that allows you to perform various actions:

1. Insert a new record
2. Delete a record
3. Update a record
4. Display records
5. Save and exit

You can navigate the menu by entering the corresponding number for each action. When inserting a new record, you will be prompted to enter the data for the record. The program will automatically generate a new ID and timestamp for the record.

When deleting or updating a record, you will be prompted to enter the ID of the record you wish to delete or update.

When displaying records, you can choose to display all records or filter records by creator or keyword.

Upon exiting the program, all records will be saved to a text file for data persistence.

## Authentication

The program supports user authentication with username and password. When starting the program, you will be prompted to log in with a username and password. If you do not have an account, you can create one by logging in as the root manager account with the username "123" and password "123". The root manager can then create new user accounts.

Each user can only see records they created. When inserting a new record, the creator of the record will be set to the current user.

## Filtering and Searching

The program supports basic filtering and keyword search for records. When displaying records, you can choose to filter records by creator or keyword. When filtering by keyword, records containing the keyword in their data will be displayed.

## Data Persistence

The program stores records in a text file for easy data persistence. When starting the program, records are loaded from the text file into memory. When exiting the program, records are saved back to the text file.

## Future Enhancements

Future enhancements to the program include adding encryption for enhanced data security and adding a web frontend for easier user access.

