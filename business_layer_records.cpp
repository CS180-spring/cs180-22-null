#include <algorithm>
#include <string>
#include <vector>

#include "business_layer_records.h"
#include "data_access_layer.h"

using namespace std;

/*
  Function: insert
  Desc: A function for the INSERT SQL command: inserts a record into a table
  Parameters: data to insert, the user info, and the database to insert in
  Return: the id of the record
*/
int insert(const std::string &data, const std::string &createdBy,
           std::vector<Record> &records) {
  Record newRecord;
  newRecord.id = getNextId(records);
  newRecord.data = data;
  newRecord.creator = createdBy;
  newRecord.timestamp = currentDateTime();
  newRecord.last_modified = currentDateTime();
  newRecord.last_read = "";
  records.push_back(newRecord);
  return newRecord.id;
}

/*
  Function: delete Record
  Desc: A function for the DELETE SQL command: deletes a record from a table
  Parameters: the id of the record to delete, the table that the record is
   located in
*/
void deleteRecord(int id, std::vector<Record> &records) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });
  if (it != records.end()) {
    it->last_modified = currentDateTime(); // Add this line
    records.erase(it);
  }
}

/*
  Function: update
  Desc: A function for the INSERT SQL command
  Parameters: id of record to update, the data to update, and the database of
   the record
*/
void update(int id, const std::string &newData, std::vector<Record> &records) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });
  if (it != records.end()) {
    it->data = newData;
    it->last_modified = currentDateTime(); // Add this line
  }
}

/*
  Function: filterByKeyword
  Desc: Searches the database table for a specific keyword and returns those
    records that match Parameters: the database table to parse and the keyword
  to search Return: all the filtered records in the database table pertaining to
  the keyword
*/
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

/*
  Function: filterByCreator
  Desc: Searches the database table for records that were created by a
    specific user Parameters: the database table to parse and the user to search
    for
  Return: all the filtered records in the database belonging to the specified
  user
*/
vector<Record> filterByCreator(const vector<Record> &records,
                               const string &createdBy) {
  vector<Record> filteredRecords;
  for (const auto &record : records) {
    if (record.creator == createdBy) {
      filteredRecords.push_back(record);
    }
  }
  return filteredRecords;
}

/*
  Function: countTermFrequency
  Desc: counts the frequency of a specific term in the data
  Parameters: the data of the record and the term to search
  Return: the number of terms counted
*/
int countTermFrequency(const string &data, const string &term) {
  int count = 0;
  size_t pos = 0;
  while ((pos = data.find(term, pos)) != string::npos) {
    count++;
    pos += term.length();
  }
  return count;
}

/*
  Function: login
  Desc: verifies the login credentials of the user and if it's correct, the user
    is successfully logged in to their account.
  Parameters: username, password, and the list of users currently in the system
  Return: the user if the login credentials match a record in the list of users
    or nullptr if the account doesn't exist or the wrong credentials were used
*/
User *login(const string &username, const string &password,
            vector<User> &users) {
  for (auto &user : users) {
    if (user.username == username && user.password == password) {
      return &user;
    }
  }
  return nullptr;
}

/*
  Function: createUser
  Desc: creates a new account with a username and password,
    along with assigning level of authority in the system
  Parameters: the new username, new password, access type, and the list of users
  in the system Return: the id of the record
*/
User *createUser(const string &username, const string &password, bool isManager,
                 vector<User> &users) {
  for (auto &user : users) {
    if (user.username == username) {
      return nullptr;
    }
  }
  User newUser{username, password, isManager};
  users.push_back(newUser);
  return &users.back();
}

/*
  Function: isManager
  Desc: Goes through the list of users in the system to see if they are a
  manager or not Parameters: the username to search and the list of users in the
  system
  Return: true or false depending on if the user is manager. If the user
  is not in the system, automatically returns as false
*/
bool isManager(const string &username, const vector<User> &users) {
  for (const auto &user : users) {
    if (user.username == username) {
      return user.isManager;
    }
  }
  return false;
}

/*

Newly Added

*/

void updateLastRead(int id, std::vector<Record> &records) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });
  if (it != records.end()) {
    it->last_read = currentDateTime();
  }
}
/*
  Function: logout
  Desc: logs out the current user in the system
  Parameters: the logged in user
*/
void logout(User *&currentUser) { currentUser = nullptr; }
