#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "data_access_layer.h"

using namespace std;

vector<Record> loadRecords() {
  vector<Record> records;
  ifstream inFile("database.txt");
  Record temp;

  while (inFile >> temp.id && getline(inFile, temp.data) &&
         getline(inFile, temp.timestamp) && getline(inFile, temp.createdBy)) {
    records.push_back(temp);
  }

  inFile.close();
  return records;
}

void saveRecords(const vector<Record> &records) {
  ofstream outFile("database.txt");

  for (const auto &record : records) {
    outFile << record.id << " " << record.data << "\n"
            << record.timestamp << "\n"
            << record.createdBy << "\n";
  }

  outFile.close();
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
