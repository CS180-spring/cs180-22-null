# Project-CS180-NULL

Please read and agree to our user agreement at the end of this document BEFORE using the software.

[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10849768&assignment_repo_type=AssignmentRepo)

Team Members (A-Z):
- Chun Ho Wong
- Cole Shirakata
- Henry Pham
- Irene Wu
- Kevin Lin

## Interface Documentation

### Overview
NullDB is a powerful database solution designed to handle basic text documents with ease. Our innovative platform provides a simple and intuitive way to store and manage text-based data, offering unparalleled performance and reliability.

### Technology
- C++
- Standard Template Library (STL)
- Algorithm
- fstream
- iostream
- string
- vector

### Interface: website (OTA)

### Features
A text-based database program built with C++. Features include:

- Managing multiple databases
- Basic insert, delete, and update functionality.
- Automatic ID generation and timestamping of records.
- User authentication with username and password, and user-specific record access.
- Root manager account for creating new user accounts.
- Basic filtering and keyword search for records.
- Data persistence through storing records in a text file.
- Exporting tables and records to JSON files.
- User ID generation for unique identification.
- Inviting users to collaborate on tables.
- Enhanced table details display.

### Getting Started
Compile and run main.cpp. Use the menu to perform actions on records.

### Authentication
Log in with username and password. Root manager can create new users. Users can only access records they created.

### Filtering and Searching
Filter records by creator or keyword.

### Data Persistence
Records and tables are stored in JSON files for easy data persistence.

### Exporting Files
Users can export tables and records to JSON files for external use.

### User ID Generation
Each user is assigned a unique ID for identification purposes.

### Collaborating on Tables
Users can invite other users to collaborate on tables by adding them as authorized collaborators.

### Enhanced Table Details Display
The table details display has been improved to align columns properly and show the owner of the table.

### Future Enhancements
Future enhancements include adding encryption for enhanced data security and adding a web frontend for easier user access.

### BurnDown Chart
[BurnDown Chart](https://docs.google.com/spreadsheets/d/1hRzuSrZP6Vtv3Y083Tg9bsVdBTbVcGTs/edit#gid=2086879608)

### Contributors
All group members contributed equally during the development. We worked on a remote online compiler, which is why the contributor list is off. We have comments to parts where we were in charge. Further code modifications will be done with Github branches and officially tracked.

---

User Agreement

By using the NullDB software (referred to as "the software" or "NullDB"), you agree to the following terms and conditions:

1. Data Responsibility: The current version of NullDB is provided as-is, without any warranty or guarantee of data integrity. We are not responsible for any data loss or corruption that may occur while using the software. It is the user's responsibility to ensure the safety and backup of their data.

2. User Account Information: Users are responsible for remembering their login information, including usernames and passwords. We do not store or have access to user passwords. If a password is lost or forgotten, it cannot be recovered, and the user may lose access to their account and associated data.

3. Record ID: Users should take note of the unique Record ID associated with each entry. Losing or forgetting a Record ID may result in difficulty locating or retrieving specific records.

4. Encryption Key: If encryption is implemented in NullDB, users are solely responsible for keeping their encryption key secure. We do not store or have access to encryption keys. Losing or forgetting an encryption key may result in permanent data loss, as we cannot recover encrypted data without the correct encryption key.

5. Importance of Data: Until further notice that the software is deemed stable, users are advised not to store any important or irreplaceable data within NullDB. The current version is under development and may have potential bugs or issues that could lead to data loss. Users should exercise caution and use the software for non-critical purposes.

6. Data Backup: It is recommended that users adopt a habit of regularly backing up their data. We suggest following the 3-2-1 backup strategy, which involves having three copies of your data, stored on at least two different storage media, with one copy stored remotely. This practice helps to mitigate the risk of data loss.

7. User Conduct: Users of NullDB are expected to comply with all applicable laws and regulations while using the software. Any misuse or unauthorized activities are strictly prohibited. We reserve the right to terminate or suspend user accounts in cases of violation or suspected misuse.

8. Limitation of Liability: In no event shall we be liable for any direct, indirect, incidental, consequential, special, or exemplary damages arising out of or in connection with the use or performance of the software, even if we have been advised of the possibility of such damages.

9. Changes to the Agreement: We reserve the right to modify or update this user agreement at any time without prior notice. Users are encouraged to review this agreement periodically for any changes.

By using NullDB, you acknowledge that you have read, understood, and agreed to the terms and conditions outlined in this user agreement. If you do not agree with these terms, you should refrain from using the software.

If you have any questions or concerns regarding this agreement, please contact us.

Last updated: 5/12/2023
