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
  std::string createdBy;
  std::string last_modified;
  std::string last_read;
};

int getNextId(const std::vector<Record> &records);
std::string currentDateTime();
int insert(const std::string &data, const std::string &createdBy,
           std::vector<Record> &records);
void deleteRecord(int id, std::vector<Record> &records);
void update(int id, const std::string &newData, std::vector<Record> &records);
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
void logout(User *&currentUser);

#endif // BUSINESS_LOGIC_LAYER_H
