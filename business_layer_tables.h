#ifndef BUSINESS_LAYER_TABLES_H
#define BUSINESS_LAYER_TABLES_H

#include "business_layer_records.h"
#include "json.hpp"

struct Table {
    int id;
    std::string owner;
    std::string name;
};


int createNewTable(const std::string &creator, std::string &tableName, std::vector<Table> &tables);

Table *loadExistingTable(const int& tableID, std::vector<Table>& tables);

void displayAllTables(const std::vector<Record> &records);

void deleteTable(std::vector<Record> &records);

#endif // BUSINESS_LAYER_TABLES_H