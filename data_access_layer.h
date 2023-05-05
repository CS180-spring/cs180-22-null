#ifndef DATA_ACCESS_LAYER_H
#define DATA_ACCESS_LAYER_H

#include "business_layer_records.h"
#include <string>
#include <vector>

std::vector<Record> loadRecords();
std::string encryptPassword(const std::string &password);
std::string decryptPassword(const std::string &encrypted_password);
void saveRecords(const std::vector<Record> &records);
std::vector<User> loadUsers();
void saveUsers(const std::vector<User> &users);

#endif // DATA_ACCESS_LAYER_H
