#ifndef BUSINESS_LAYER_TABLES_H
#define BUSINESS_LAYER_TABLES_H

#include "business_layer_records.h"

void createNewTable(std::vector<Record> &records);

void loadExistingTable(std::vector<Record> &records);

void displayAllTables(const std::vector<Record> &records);

void deleteTable(std::vector<Record> &records);

#endif // BUSINESS_LAYER_TABLES_H