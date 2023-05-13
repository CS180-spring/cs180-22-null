#include "data_layer_tables.h"
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

vector<Table> loadTables() {
  vector<Table> tables{};

  ifstream ifs("tables.json");
  if (ifs.is_open()) {
    json j_tables;
    ifs >> j_tables;

    for (const auto &j_table : j_tables) {
      Table table;
      table.id = j_table["id"];
      table.owner = j_table["owner"];
      table.name = j_table["name"];
    }
    ifs.close();
  }
  return tables;
}

int getNextID(const vector<Table> &tables) {
  int maxId = 0;
  for (const auto &table : tables) {
    if (table.id > maxId) {
      maxId = table.id;
    }
  }
    return maxId + 1;
}