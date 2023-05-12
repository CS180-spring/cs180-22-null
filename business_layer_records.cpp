#include "business_layer_records.h"
#include "data_access_layer.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Password and XOR key as input. Outputs encrypted password string.
string encryptRecord(const string &password, const string &XOR_KEY) {
  if (XOR_KEY.empty()) {
    throw invalid_argument("XOR_KEY must not be empty.");
  }
  string encrypted_password = password;
  int key_length = XOR_KEY.length();
  for (int i = 0; i < encrypted_password.length(); i++) {
    encrypted_password[i] = encrypted_password[i] ^ XOR_KEY[i % key_length];
  }
  return encrypted_password;
}

// Takes encrypted password and XOR key as input. Outputs decrypted password.
string decryptRecord(const string &encrypted_password, const string &XOR_KEY) {
  if (XOR_KEY.empty()) {
    throw invalid_argument("XOR_KEY must not be empty.");
  }
  string password = encrypted_password;
  int key_length = XOR_KEY.length();
  for (int i = 0; i < password.length(); i++) {
    password[i] = password[i] ^ XOR_KEY[i % key_length];
  }
  return password;
}

// Returns string signature by calculating hash.
std::string generateSignature(const std::string &str) {
  std::hash<std::string> hasher;
  size_t hash = hasher(str);
  return std::to_string(hash);
}

string getDecryptKey() { // Helper
  string key;
  cout << "Enter the decryption key: ";
  getline(cin, key);
  return key;
}

/*
  Function: insert
  Desc: A function for the INSERT SQL command: inserts a record into a table
  Parameters: data to insert, the user info, and the database to insert in
  Return: the id of the record
*/
int insert(const string &data, const string &createdBy, vector<Record> &records,
           const int encryption, const string &cryptKey) {
  Record newRecord;
  newRecord.id = getNextId(records);
  newRecord.data = data;
  newRecord.creator = createdBy;
  newRecord.timestamp = currentDateTime();
  newRecord.last_modified = currentDateTime();
  newRecord.last_read = "";
  newRecord.encryptionType = "NONE";
  newRecord.signature =
      generateSignature(data); // This would keep the unencrypted signature
  if (encryption == 1) {
    newRecord.data = encryptRecord(newRecord.data, cryptKey);
    newRecord.encryptionType = "XOR";
  }
  records.push_back(newRecord);
  return newRecord.id;
}

/*
  Function: delete Record
  Desc: A function for the DELETE SQL command: deletes a record from a table
  Parameters: the id of the record to delete, the table that the record is
   located in
*/
void deleteRecord(int id, vector<Record> &records, const string &password) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });

  if (it != records.end()) {
    if (it->encryptionType != "NONE") {
      string decryptedData = decryptRecord(it->data, password);
      if (generateSignature(decryptedData) != it->signature) {
        cout << "decryptedData signature unmatch:"
             << generateSignature(decryptedData) << endl;
        cout << "Invalid decryption key." << endl;
        return;
      }
    }
    it->last_modified = currentDateTime();
    records.erase(it);
  }
}

/*
  Function: update
  Desc: A function for the INSERT SQL command
  Parameters: id of record to update, the data to update, and the database of
   the record
*/
void update(int id, const string &newData, vector<Record> &records,
            const string &password) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });

  if (it != records.end()) {
    if (it->encryptionType != "NONE") {
      string decryptedData = decryptRecord(it->data, password);
      if (generateSignature(decryptedData) != it->signature) {
        cout << "Invalid decryption key." << endl;
        return;
      }
    }
    it->data = newData;
    it->last_modified = currentDateTime();
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

void updateLastRead(int id, vector<Record> &records) {
  auto it = find_if(records.begin(), records.end(),
                    [id](const Record &record) { return record.id == id; });
  if (it != records.end()) {
    it->last_read = currentDateTime();
  }
}

Record getRecordById(int id, const vector<Record> &records) {
  auto temp = find_if(records.begin(), records.end(),
                      [id](const Record &record) { return record.id == id; });

  if (temp != records.end()) {
    return *temp;
  } else {
    throw invalid_argument("Record with specified ID does not exist.");
  }
}

vector<Record> displayRecord(int id, const vector<Record> &records,
                             User *currentUser, const string &password) {
  vector<Record> temp;
  auto record = getRecordById(id, records);

  if (record.creator == currentUser->username || currentUser->isManager) {
    if (record.encryptionType != "NONE") {
      record.data = decryptRecord(record.data, password);
      if (generateSignature(record.data) != record.signature) {
        cout << "decryptedData signature unmatch:"
             << generateSignature(record.data) << endl;
        cout << "DEBUG MESSAGE: " << record.data << endl;
        cout << "Invalid decryption key." << endl;
        return temp;
      }
    }
    temp.push_back(record);
  }
  return temp;
}

bool compareByData(const Record &a, const Record &b) { return a.data < b.data; }

bool compareById(const Record &a, const Record &b) { return a.id < b.id; }

void sortRecords(vector<Record> &records, bool reverse) {
  if (reverse) {
    sort(records.rbegin(), records.rend(), compareByData);
  } else {
    sort(records.begin(), records.end(), compareByData);
  }
}

void sortRecordsById(vector<Record> &records, bool reverse) {
  if (reverse) {
    sort(records.rbegin(), records.rend(), compareById);
  } else {
    sort(records.begin(), records.end(), compareById);
  }
}

// New patches End
