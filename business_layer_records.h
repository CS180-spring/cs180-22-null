#ifndef BUSINESS_LOGIC_LAYER_H
#define BUSINESS_LOGIC_LAYER_H

#include <string>
#include <vector>

struct User {
  std::string username;
  std::string password;
  bool isManager;
};

struct Record {
  int id;
  std::string data;
  std::string timestamp;
  std::string last_modified;
  std::string last_read;
  std::string creator;
  std::string encryptionType = "NONE";
  std::string signature;
};

std::string encryptRecord(const std::string &password,
                          const std::string &XORKEY);
std::string decryptRecord(const std::string &password,
                          const std::string &XORKEY);

int getNextId(const std::vector<Record> &records);
std::string currentDateTime();
int insert(const std::string &data, const std::string &createdBy,
           std::vector<Record> &records, const int encryption,
           const std::string &cryptKey);

void deleteRecord(int id, std::vector<Record> &records,
                  const std::string &password);
void update(int id, const std::string &newData, std::vector<Record> &records,
            const std::string &password);

std::vector<Record> filterByKeyword(const std::vector<Record> &records,
                                    const std::string &keyword);
std::vector<Record> filterByCreator(const std::vector<Record> &records,
                                    const std::string &createdBy);
int countTermFrequency(const std::string &data, const std::string &term);
User *login(const std::string &username, const std::string &password,
            std::vector<User> &users);
User *createUser(const std::string &username, const std::string &password,
                 bool isManager, std::vector<User> &users);
bool isManager(const std::string &username, const std::vector<User> &users);
void updateLastRead(int id, std::vector<Record> &records);
bool logout(User *&currentUser);

Record getRecordById(int id, const std::vector<Record> &records);
std::vector<Record> displayRecord(int id, const std::vector<Record> &records,
                                  User *currentUser,
                                  const std::string &password);
void sortRecords(std::vector<Record> &records, bool reverse);
void sortRecordsById(std::vector<Record> &records, bool reverse);
bool compareByData(const Record &a, const Record &b);
bool compareById(const Record &a, const Record &b);

#endif // BUSINESS_LOGIC_LAYER_H
