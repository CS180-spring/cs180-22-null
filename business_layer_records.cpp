#include "business_layer_records.h"
#include "data_layer_records.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

string encryptXOR(const string &password, const string &XOR_KEY) {
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

string decryptXOR(const string &encrypted_password, const string &XOR_KEY) {
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

///
/// TEA ENCRYPTION
/// HP 05/11/2023

vector<unsigned int> encryptTEA(const vector<unsigned int> &password,
                                const vector<unsigned int> TEAKEY) {
  unsigned int p0 = password[0], p1 = password[1], sum = 0;
  unsigned int delta = 0x9e3779b9;
  unsigned int k0 = TEAKEY[0], k1 = TEAKEY[1], k2 = TEAKEY[2], k3 = TEAKEY[3];

  for (int i = 0; i < 32; ++i) {
    sum += delta;
    p0 += ((p1 << 4) + k0) ^ (p1 + sum) ^ ((p1 >> 5) + k1);
    p1 += ((p0 << 4) + k2) ^ (p0 + sum) ^ ((p0 >> 5) + k3);
  }

  vector<unsigned int> encrypted_password{};
  encrypted_password[0] = p0;
  encrypted_password[1] = p1;

  return encrypted_password;
}

vector<unsigned int> decryptTEA(const vector<unsigned int> &encrypted_password,
                                const vector<unsigned int> TEAKEY) {
  unsigned int p0 = encrypted_password[0], p1 = encrypted_password[1],
               sum = 0xC6EF3720, i;
  unsigned int delta = 0x9e3779b9;
  unsigned int k0 = TEAKEY[0], k1 = TEAKEY[1], k2 = TEAKEY[2], k3 = TEAKEY[3];
  for (i = 0; i < 32; i++) {
    p1 -= ((p0 << 4) + k2) ^ (p0 + sum) ^ ((p0 >> 5) + k3);
    p0 -= ((p1 << 4) + k0) ^ (p1 + sum) ^ ((p1 >> 5) + k1);
    sum -= delta;
  }

  vector<unsigned int> password{};
  password[0] = p0;
  password[1] = p1;

  return password;
}

string generateSignature(const string &str) {
  hash<string> hasher;
  size_t hash = hasher(str);
  return to_string(hash);
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
    newRecord.data = encryptXOR(newRecord.data, cryptKey);
    newRecord.encryptionType = "XOR";
  }
  /*// KL, 05/11/2023
  if (encryption == 2) {
    newRecord.data = encryptTEA(newRecord.data, cryptKey);
    newRecord.encryptionType = "TEA";
  }
*/
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
      string decryptedData = decryptXOR(it->data, password);
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
      string decryptedData = decryptXOR(it->data, password);
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
  to search Return: all the filtered records in the database table pertaining
  to the keyword
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
    specific user Parameters: the database table to parse and the user to
  search for Return: all the filtered records in the database belonging to the
  specified user
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
    if (record.encryptionType == "XOR") {
      record.data = decryptXOR(record.data, password);
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
