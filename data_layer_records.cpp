#include "data_layer_records.h"
//kl
//#include "business_layer_records.h"
#include "json.hpp"
#include <algorithm>
#include <bitset>
#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
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
      record.tableID = j_record["tableID"];
      record.tableName = j_record["tableName"];
      record.data = j_record["data"];
      record.creator = j_record["creator"];
      record.timestamp = j_record["timestamp"];
      record.last_modified = j_record["last_modified"];
      record.last_read = j_record["last_read"];
      record.encryptionType = j_record["encryptionType"];
      record.signature = j_record["signature"];
      records.push_back(record);
    }

    ifs.close();
  }

  return records;
}

void saveRecords(const vector<Record> &records) {
  json j_records = json::array();
  // KL, 05/19
cout << "This is saveRecords, before" << endl;
  
  
  for (const Record &record : records) {
    json j_record = {{"id", record.id},
                     {"tableID", record.tableID},
                     {"tableName", record.tableName},
                     {"data", record.data},
                     {"creator", record.creator},
                     {"timestamp", record.timestamp},
                     {"last_modified", record.last_modified},
                     {"last_read", record.last_read},
                     {"encryptionType", record.encryptionType},
                     {"signature", record.signature}};
                      // KL, 05/19
                      cout << "This is saveRecords, during" << endl;
                      cout << "tableName: " << record.tableName << endl << endl;
    j_records.push_back(j_record);
  }

  ofstream ofs("records.json");
  ofs << j_records.dump(4) << endl;
  ofs.close();
}

// New Patches




// New Patches End

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
