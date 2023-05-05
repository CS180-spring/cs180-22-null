#include "data_access_layer.h"
#include "json.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

const string XOR_KEY = "TEAMNULL";

string encryptPassword(const string &password) {
  string encrypted_password = password;
  int key_length = XOR_KEY.length();
  for (int i = 0; i < encrypted_password.length(); i++) {
    if (isalnum(encrypted_password[i])) {
      encrypted_password[i] = encrypted_password[i] ^ XOR_KEY[i % key_length];
    }
  }
  return encrypted_password;
}

string decryptPassword(const string &encrypted_password) {
  string password = encrypted_password;
  int key_length = XOR_KEY.length();
  for (int i = 0; i < password.length(); i++) {
    if (isalnum(password[i])) {
      password[i] = password[i] ^ XOR_KEY[i % key_length];
    }
  }
  return password;
}

vector<Record> loadRecords() {
  vector<Record> records;

  ifstream ifs("records.json");
  if (ifs.is_open()) {
    json j_records;
    ifs >> j_records;

    for (const auto &j_record : j_records) {
      Record record;
      record.id = j_record["id"];
      record.data = j_record["data"];
      record.creator = j_record["creator"];
      record.timestamp = j_record["timestamp"];
      record.last_modified = j_record["last_modified"];
      record.last_read = j_record["last_read"];
      records.push_back(record);
    }

    ifs.close();
  }

  return records;
}

void saveRecords(const vector<Record> &records) {
  json j_records = json::array();

  for (const Record &record : records) {
    json j_record = {{"id", record.id},
                     {"data", record.data},
                     {"creator", record.creator},
                     {"timestamp", record.timestamp}};
    j_records.push_back(j_record);
  }

  ofstream ofs("records.json");
  ofs << j_records.dump(4) << endl;
  ofs.close();
}

vector<User> loadUsers() {
  vector<User> users;

  ifstream inFile("users.json");
  if (inFile.is_open()) {
    json j_users;
    inFile >> j_users;

    for (const auto &j_user : j_users) {
      User user;
      user.username = j_user["username"];
      user.password = decryptPassword(j_user["password"]);
      user.isManager = j_user["isManager"];
      users.push_back(user);
    }

    inFile.close();
  }

  return users;
}

void saveUsers(const vector<User> &users) {
  json j_users = json::array();

  for (const User &user : users) {
    json j_user = {{"username", user.username},
                   {"password", encryptPassword(user.password)},
                   {"isManager", user.isManager}};
    j_users.push_back(j_user);
  }

  ofstream outFile("users.json");
  outFile << j_users.dump(4) << endl;
  outFile.close();
}

int getNextId(const vector<Record> &records) {
  int maxId = 0;
  for (const auto &record : records) {
    if (record.id > maxId) {
      maxId = record.id;
    }
  }
  return maxId + 1;
}

string currentDateTime() {
  time_t now = time(0);
  tm *localtm = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtm);
  return string(buffer);
}
