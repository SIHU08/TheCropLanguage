#include <any>
#include <iostream>
#include <string>

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
  }
  return "INVALID_VALUE";
}
