#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct User {
  string username;
  string password;
  bool isManager;
};

struct Record {
  int id;
  string data;
  string timestamp;
  string createdBy;
};

// HP
// uploads saved records for display
vector<Record> loadRecords() {
  vector<Record> records; // creates the database for records
  ifstream inFile("database.txt"); // uses the textfile where the records are stored
  Record temp; // temporary variable to store records in

  while (inFile >> temp.id && getline(inFile, temp.data) &&
         getline(inFile, temp.timestamp) && getline(inFile, temp.createdBy)) {
    records.push_back(temp); //loop reads the file for records, stores it into the temp variable and then pushes that record into the database when booted for display
  }

  inFile.close();
  return records;
}

// HP
// saves database records upon closing the program
void saveRecords(const vector<Record> &records) {
  ofstream outFile("database.txt"); //file to save records in

  for (const auto &record : records) {
    outFile << record.id << " " << record.data << "\n"
            << record.timestamp << "\n"
            << record.createdBy << "\n";
  } // writes the record onto the file

  outFile.close(); //closes the file
}

vector<User> loadUsers() {
  vector<User> users;
  ifstream inFile("users.txt");
  User temp;

  while (inFile >> temp.username >> temp.password >> temp.isManager) {
    users.push_back(temp);
  }

  inFile.close();
  return users;
}

void saveUsers(const vector<User> &users) {
  ofstream outFile("users.txt");

  for (const auto &user : users) {
    outFile << user.username << " " << user.password << " " << user.isManager
            << "\n";
  }

  outFile.close();
}

// HP
// increments ID for insertion
int getNextId(const vector<Record> &records) {
  int maxId = 0;
  for (const auto &record : records) { // iterates through the entire database
    if (record.id > maxId) {
      maxId = record.id;  // updates the last record as the highest ID numebr
    }
  }
  return maxId + 1; //increments ID number to be assigned as the next ID
}

string currentDateTime() {
  time_t now = time(0);
  tm *localtm = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtm);
  return string(buffer);
}

// HP
// inserts new record
int insert(const string &data, const string &createdBy,
           vector<Record> &records) {
  int id = getNextId(records); // assign ID
  string timestamp = currentDateTime(); // timestamp of when created
  records.push_back({id, data, timestamp, createdBy}); // pushes the new record onto the database
  return id;
}

void deleteRecord(int id, vector<Record> &records) {
  records.erase(remove_if(records.begin(), records.end(),
                          [id](const Record &r) { return r.id == id; }),
                records.end());
}

// CW 2023
// Basic update function 
void update(int id, const string &newData, vector<Record> &records) {
  for (auto &record : records) { // loop thur all the data
    if (record.id == id) { // locate the data with the ID
      record.data = newData; // Replace it
      break;
    }
  }
}

vector<Record> filterByKeyword(const vector<Record> &records,
                               const string &keyword) {
  vector<Record> filteredRecords;
  for (const auto &record : records) {
    if (record.data.find(keyword) != string::npos) {
      filteredRecords.push_back(record);
    }
  }
  return filteredRecords;
}

// CW 2023
// Read function, since each user only suppose to read what they "own" 
vector<Record> filterByCreator(const vector<Record> &records,
                               const string &createdBy) {
  vector<Record> filteredRecords;
  for (const auto &record : records) {
    if (record.createdBy == createdBy) {
      filteredRecords.push_back(record);
    }
  }
  return filteredRecords;
}

int countTermFrequency(const string &data, const string &term) {
  int count = 0;
  size_t pos = 0;
  while ((pos = data.find(term, pos)) != string::npos) {
    count++;
    pos += term.length();
  }
  return count;
}

User *login(const string &username, const string &password,
            vector<User> &users) {
  for (auto &user : users) {
    if (user.username == username && user.password == password) {
      return &user;
    }
  }
  return nullptr;
}

User *createUser(const string &username, const string &password, bool isManager,
                 vector<User> &users) {
  User newUser{username, password, isManager};
  users.push_back(newUser);
  return &users.back();
}

bool isManager(const string &username, const vector<User> &users) {
  for (const auto &user : users) {
    if (user.username == username) {
      return user.isManager;
    }
  }
  return false;
}

void logout(User *&currentUser) { currentUser = nullptr; }

int main() {
  vector<Record> records = loadRecords();
  vector<User> users = loadUsers();

  if (!isManager("123", users)) {
    createUser("123", "123", true, users);
    saveUsers(users);
  }

  User *currentUser = nullptr;

  while (!currentUser) {
    int choice;
    cout << "1. Log in\n2. Create user\nChoose an option: ";
    cin >> choice;

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (choice == 1) {
      currentUser = login(username, password, users);
      if (!currentUser) {
        cout << "Invalid credentials. Please try again." << endl;
      }
    } else if (choice == 2) {
      bool isManager = false;
      if (currentUser && currentUser->isManager) {
        cout << "Do you want to make the new user a system manager? (yes/no): ";
        string response;
        cin >> response;
        if (response == "yes") {
          isManager = true;
        }
      }
      currentUser = createUser(username, password, isManager, users);
      saveUsers(users);
      if (!currentUser) {
        cout << "Error creating user. Please try again." << endl;
      }
    } else {
      cout << "Invalid choice! Please try again." << endl;
    }
  }

  // for Kevin: remember to update the choice/user choice menu accordingly to the later updates and changes.
  // the goal is separate the choice menu from the function themselves
  int choice;
  while (true) {
    cout << "1. Insert\n2. Delete\n3. Update\n4. Display Records\n5. Keyword "
            "Search\n6. Term Frequency\n7. Save and "
            "Exit\n8. Log out \n Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      string data;
      cin.ignore();
      cout << "Enter data: ";
      getline(cin, data);
      int id = insert(data, currentUser->username, records);
      cout << "Inserted record with id: " << id << endl;
    } else if (choice == 2) {
      int id;
      cout << "Enter id to delete: ";
      cin >> id;
      deleteRecord(id, records);
    } else if (choice == 3) {
      int id;
      string newData;
      cout << "Enter id to update: ";
      cin >> id;
      cin.ignore();
      cout << "Enter new data: ";
      getline(cin, newData);
      update(id, newData, records);
    } else if (choice == 4) {
      for (const auto &record :
           filterByCreator(records, currentUser->username)) {
        cout << record.id << ": " << record.data
             << " (Created at: " << record.timestamp << ")" << endl;
      }
    } else if (choice == 5) {
      string keyword;
      cout << "Enter keyword: ";
      cin >> keyword;
      for (const auto &record : filterByKeyword(
               filterByCreator(records, currentUser->username), keyword)) {
        cout << record.id << ": " << record.data
             << " (Created at: " << record.timestamp << ")" << endl;
      }
    } else if (choice == 6) {
      string term;
      cout << "Enter term: ";
      cin >> term;
      int totalFrequency = 0;
      for (const auto &record :
           filterByCreator(records, currentUser->username)) {
        int frequency = countTermFrequency(record.data, term);
        totalFrequency += frequency;
        if (frequency > 0) {
          cout << "Record ID " << record.id << ": " << frequency
               << " occurrences" << endl;
        }
      }
      cout << "Total occurrences of term \"" << term << "\": " << totalFrequency
           << endl;
    } else if (choice == 7) {
      saveRecords(records);
      break;
    } else if (choice == 8) {
      logout(currentUser);
      break;
    } else {
      cout << "Invalid choice!" << endl;
    }
  }
  return 0;
}
