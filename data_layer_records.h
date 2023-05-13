#ifndef DATA_LAYER_RECORDS_H
#define DATA_LAYER_RECORDS_H

#include "business_layer_records.h"
#include <string>
#include <vector>

std::vector<Record> loadRecords();
void saveRecords(const std::vector<Record> &records);
int getNextId(const std::vector<Record> &records);
std::string currentDateTime();

#endif // DATA_LAYER_RECORDS_H
