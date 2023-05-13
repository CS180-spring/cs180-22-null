#include "business_layer_tables.h"
#include "data_layer_tables.h"

using namespace std;

int createNewTable(const string &creator, string &tableName, vector<Table> &tables)
{
  Table newTable;
  newTable.id = getNextID(tables);
  newTable.owner = creator;
  newTable.name = tableName;

  tables.push_back(newTable);
  return newTable.id;
}

Table *loadExistingTable(const int& tableID, std::vector<Table>& tables) {
  for (auto& table : tables) {
    if (table.id == tableID) { return &table; }
  }
  return nullptr;
}