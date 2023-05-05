#include "data_access_layer.h"
#include "json.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

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
  ofs << setw(4) << j_records << endl;
  ofs.close();
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
