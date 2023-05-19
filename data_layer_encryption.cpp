#include "data_layer_encryption.h"

using namespace std;

// CHATGPT HELPS
string base64_encode(const string &in) {
  string out;

  int val = 0, valb = -6;
  for (unsigned char c : in) {
    val = (val << 8) + c;
    valb += 8;
    while (valb >= 0) {
      out.push_back(
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
              [(val >> valb) & 0x3F]);
      valb -= 6;
    }
  }
  if (valb > -6)
    out.push_back(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
            [((val << 8) >> (valb + 8)) & 0x3F]);
  while (out.size() % 4)
    out.push_back('=');
  return out;
}

// CHATGPT HELPS
string base64_decode(const string &in) {
  string out;

  vector<int> T(256, -1);
  for (int i = 0; i < 64; i++)
    T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] =
        i;

  int val = 0, valb = -8;
  for (unsigned char c : in) {
    if (T[c] == -1)
      break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0) {
      out.push_back(char((val >> valb) & 0xFF));
      valb -= 8;
    }
  }
  return out;
}

// Lucky Number 8

string encryptString(const string &str) {
  string encrypted = base64_encode(str);
  for_each(encrypted.begin(), encrypted.end(),
           [](char &c) { c = c + 8; }); // Caesar Cipher
  return encrypted;
}

string decryptString(const string &str) {
  string decrypted = str;
  for_each(decrypted.begin(), decrypted.end(),
           [](char &c) { c = c - 8; }); // Caesar Cipher
  return base64_decode(decrypted);
}
