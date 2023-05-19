#include "business_layer_tables.h"
#include "data_layer_tables.h"
#include <iomanip>

using namespace std;
int createNewTable(const string &creator, string &tableName,
                   vector<Table> &tables) {
  Table newTable;
  newTable.id = getNextID(tables);
  newTable.owner = creator;
  newTable.name = tableName;

  tables.push_back(newTable);
  return newTable.id;
}

Table *loadExistingTable(const int &tableID, std::vector<Table> &tables) {
  for (auto &table : tables) {
    if (table.id == tableID) {
      return &table;
    }
  }
  return nullptr;
}

void printTableDetails(const std::vector<Table> &tables) {
  cout << "╠═══════════════════════════════════════════════════════════════════"
          "════════════════╣"
       << endl;
  cout << "║ ID ║       Owner       ║        Name        ║  Authorized "
          "Collaborators  ║"
       << endl;
  cout << "╠═══════════════════════════════════════════════════════════════════"
          "════════════════╣"
       << endl;

  for (const auto &table : tables) {
    cout << "║ " << setw(2) << table.id << " ║ " << setw(18) << table.owner
         << " ║ " << setw(19) << table.name << " ║ ";

    if (!table.authorizedCollaborators.empty()) {
      // Calculate total width of authorized collaborators column
      int totalWidth = 27;
      for (const auto &collab : table.authorizedCollaborators) {
        totalWidth += to_string(collab).length() + 1;
      }

      // Print authorized collaborators
      for (const auto &collab : table.authorizedCollaborators) {
        cout << collab << " ";
      }

      // Adjust setw() value to maintain alignment
      cout << setw(totalWidth - 2 * table.authorizedCollaborators.size()) << "║"
           << endl;
    } else {
      // If no authorized collaborators, print empty column with proper
      // alignment
      cout << setw(27) << "║" << endl;
    }
  }

  cout << "╚═══════════════════════════════════════════════════════════════════"
          "════════════════╝"
       << endl;
}
