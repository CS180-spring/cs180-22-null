#include "presentation_layer.h"
#include "business_layer_records.h"
#include "data_access_layer.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

// CHATGPT HELP
void setStdinEcho(bool enable) {
  termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  if (!enable)
    tty.c_lflag &= ~ECHO;
  else
    tty.c_lflag |= ECHO;

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

// CHATGPT HELP
string getPassword() {
  string password;
  char ch;
  setStdinEcho(false);

  // censors the password
  while ((ch = getchar()) != '\n') {
    if (ch != 127 && ch != 8) { // Ignore delete and backspace keys
      password.push_back(ch);
      cout << '*';
    } else if (!password
                    .empty()) { // Remove the last character from the password
      password.pop_back();
      cout << "\b \b"; // Move cursor back, overwrite with space, and move
                       // cursor back again
    }
  }

  setStdinEcho(true);
  cout << endl;
  return password;
}

void createNewTable(vector<Record> &records) {
  cout << "Creating new table..." << endl;
}

void loadExistingTable(vector<Record> &records) {
  cout << "Loading existing table..." << endl;
}

void displayAllTables(const vector<Record> &records) {
  cout << "Displaying all tables..." << endl;
}

void deleteTable(vector<Record> &records) {
  cout << "Deleting table..." << endl;
}

int main() {
  vector<Record> records = loadRecords();
  vector<User> users = loadUsers();

  if (!isManager("123", users)) {
    createUser("123", "123", true, users);
    createUser("1233", "1233", false, users);
    saveUsers(users);
  }

  User *currentUser = nullptr;
  User *debug = nullptr; // Later on, convert this into Table ptr

  while (!currentUser) {
    int choice;
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║                                              ║" << endl;
    cout << "║         Welcome to the NullDB!               ║" << endl;
    cout << "║                                              ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║ 1. Log in                                    ║" << endl;
    cout << "║ 2. Create user                               ║" << endl;
    cout << "║                                              ║" << endl;
    cout << "║ Choose an option:                            ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cin >> choice;

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin.ignore();
    password = getPassword();

    if (choice == 1) {
      currentUser = login(username, password, users);
      if (!currentUser) {
        cout << "Invalid credentials. Please try again." << endl;
      } else {
        cout << "Welcome, " << currentUser->username << "!" << endl;
      }
    } else if (choice == 2) {
      bool isManager = false;
      string managerCode = "CDkey123";
      cout << "Do you want to make the new user a system manager? (yes/no): ";
      string response;
      cin >> response;
      if (response == "yes") {
        cout << "Enter the manager code: ";
        string code;
        cin >> code;
        if (code == managerCode) {
          isManager = true;
        } else {
          cout << "Invalid code. User will not be a manager.\n";
        }
      }
      currentUser = createUser(username, password, isManager, users);
      saveUsers(users);
      if (!currentUser) {
        cout << "User name is taken. Please try again." << endl;
      } else {
        cout << "User created successfully!" << endl;
      }
    } else {
      cout << "Invalid choice! Please try again." << endl;
    }
  }

  while (!debug) {
    int choice;
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║                                              ║" << endl;
    cout << "║                  Table  Menu                 ║" << endl;
    cout << "║                                              ║" << endl;
    cout << "╠══════════════════════════════════════════════╣" << endl;
    cout << "║ 1. Create a table                            ║" << endl;
    cout << "║ 2. View all tables                           ║" << endl;
    cout << "║ 3. Go into a table                           ║" << endl;
    cout << "║ 4. Delete a table                            ║" << endl;
    cout << "║ 5. Exit                                      ║" << endl;
    cout << "║ 6. Debug                                     ║" << endl;
    cout << "║                                              ║" << endl;
    cout << "║ Choose an option:                            ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Option 1: Create a table." << endl;
      break;
    case 2:
      cout << "Option 2: View all tables." << endl;
      break;
    case 3:
      cout << "Option 3: Go into a table." << endl;
      break;
    case 4:
      cout << "Option 4: Delete a table." << endl;
      break;
    case 5:
      cout << "Exiting NullDB. Goodbye!" << endl;
      return 0;
    case 6:
      debug = currentUser;
      break;
    default:
      cout << "Invalid choice! Please try again." << endl;
    }

    while (true) {
      int choice;
      cout << "╔══════════════════════════════════════════════╗" << endl;
      cout << "║                                              ║" << endl;
      cout << "║        Welcome to the NullDB!                ║" << endl;
      cout << "║                                              ║" << endl;
      cout << "╠══════════════════════════════════════════════╣" << endl;
      cout << "║ Welcome, " << currentUser->username
           << setw(39 - currentUser->username.length()) << "║" << endl;
      cout << "╠══════════════════════════════════════════════╣" << endl;
      cout << "║ 1. Insert                                    ║" << endl;
      cout << "║ 2. Delete                                    ║" << endl;
      cout << "║ 3. Update                                    ║" << endl;
      cout << "║ 4. Display Records                           ║" << endl;
      cout << "║ 5. Keyword Search                            ║" << endl;
      cout << "║ 6. Term Frequency                            ║" << endl;
      cout << "║ 7. Save and Exit                             ║" << endl;
      cout << "║ 8. Log out                                   ║" << endl;
      cout << "║                                              ║" << endl;
      cout << "║ Enter your choice:                           ║" << endl;
      cout << "╚══════════════════════════════════════════════╝" << endl;

      cin >> choice;

      switch (choice) {
      case 1: {
        string data;
        cin.ignore();
        cout << "Enter data: ";
        getline(cin, data);
        int id = insert(data, currentUser->username, records);
        cout << "Inserted record with id: " << id << endl;
        break;
      }
      case 2: {
        int id;
        cout << "Enter id to delete: ";
        cin >> id;
        deleteRecord(id, records);
        break;
      }
      case 3: {
        int id;
        string newData;
        cout << "Enter id to update: ";
        cin >> id;
        cin.ignore();
        cout << "Enter new data: ";
        getline(cin, newData);
        update(id, newData, records);
        break;
      }
      case 4: {
        for (const auto &record :
             filterByCreator(records, currentUser->username)) {
          updateLastRead(record.id, records);
          cout << record.id << ": " << record.data
               << " (Created at: " << record.timestamp
               << ", Last modified: " << record.last_modified
               << ", Last read: ";
          if (record.last_read.empty()) {
            cout << "Never been read";
          } else {
            cout << record.last_read;
          }
          cout << ")" << endl;
        }
        break;
      }
      case 5: {
        string keyword;
        cout << "Enter keyword: ";
        cin >> keyword;
        for (const auto &record : filterByKeyword(
                 filterByCreator(records, currentUser->username), keyword)) {
          cout << record.id << ": " << record.data
               << " (Created at: " << record.timestamp << ")" << endl;
        }
        break;
      }
      case 6: {
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
        cout << "Total occurrences of term \"" << term
             << "\": " << totalFrequency << endl;
        break;
      }
      case 7: {
        saveRecords(records);
        break;
      }
      case 8: {
        logout(currentUser);
        break;
      }
      default: {
        cout << "Invalid choice!" << endl;
        break;
      }
        return 0;
      }
    }
  }
}
