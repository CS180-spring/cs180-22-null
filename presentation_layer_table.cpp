#include "presentation_layer_table.h"
#include "data_layer_records.h"
#include "presentation_layer.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

void printTables(User *currentUser) {
  vector<Record> records = loadRecords();
  /*

  for (const auto &table :
                filterByUser(tables, currentUser->username)) {
    cout <<
  "╔══════════════════════════════════════════════════════════════════════════════════════╗"
  << endl; cout << "║                               table.name ║" << endl;
  */
  string data = "";
  cout << "╠═══════════════════════════════════════════════════════════════════"
          "═══════════════════╣"
       << endl;
  cout << "║ ID ║ Creator ║         Data         ║       Signature       ║     "
          "  Timestamp        ║"
       << endl;
  cout << "╠═══════════════════════════════════════════════════════════════════"
          "═══════════════════╣"
       << endl;
  for (const auto &record : filterByCreator(records, currentUser->username)) {
    if (record.encryptionType != "NONE") {
      data = "ENCRYPTED";
    } else {
      data = record.data;
    }
    cout << "║" << setw(3) << record.id << " ║" << setw(8) << record.creator
         << " ║" << setw(21) << data << " ║" << setw(22) << record.signature
         << " ║" << setw(23) << record.timestamp << " ║" << endl;
  } // end record while
  /*
  } // end table while
    */

  cout << "╚═══════════════════════════════════════════════════════════════════"
          "═══════════════════╝"
       << endl;
}