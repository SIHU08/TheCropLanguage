#include <any>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

string to_string(any value) {
  if (value.type() == typeid(int)) {
    return to_string(any_cast<int>(value));
  } else if (value.type() == typeid(double)) {
    return to_string(any_cast<double>(value));
  } else if (value.type() == typeid(char)) {
    return string(1, any_cast<char>(value));
  } else if (value.type() == typeid(bool)) {
    return any_cast<bool>(value) ? "true" : "false";
  } else if (value.type() == typeid(string)) {
    return any_cast<string>(value);
  }
  return "INVALID_VALUE";
}

vector<string> splitWithRegex(string s, const string& pattern = " ") {
  regex re(pattern);
  sregex_token_iterator it(s.begin(), s.end(), re, -1), end;
  vector<string> answer(it, end);
  return answer;
}

string genRandomString(int len) {
  static const char alphanum[] = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
  string res;
  for (int i = 0; i < len; ++i)
    res += alphanum[rand() % (sizeof(alphanum) - 1)];

  return res;
}