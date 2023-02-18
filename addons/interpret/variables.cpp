#include <any>
#include <iostream>
#include <map>
#include <string>
#include <regex>

#include "cropaddon.h"
#include "datas.h"

any getVariableValue(Variable variable) {
  VariableType type = variable.type.type;
  if (type == VOID) {
    // WTF...??
  } else if (type == INT) {
    return any_cast<int>(variable.value);
  } else if (type == FLOAT) {
    return any_cast<double>(variable.value);
  } else if (type == CHAR) {
    return any_cast<char>(variable.value);
  } else if (type == BOOL) {
    return any_cast<bool>(variable.value);
  } else if (type == OBJECT) {
    return any_cast<string>(variable.value);
    //    cerr << "e guo sse nun sa ram da zuk er"
//         << "\n";
//    exit(1);
  } else {
    cerr << "WTF"
         << "\n";
    exit(1);
  }
  return nullptr;
}

Variable getVariableOrTemporaryVariable(string value,
                                        map<string, Variable> variableMap) {
  if (variableMap.count(value))
    return variableMap[value];

  if (value[0] == '\"' && value[value.size() - 1] == '\"') { // is String
    return {Type(OBJECT), value.substr(1, value.size() - 2)};
  } else if (value[0] == '\'' && value[value.size() - 1] == '\'') { // is char
    return {Type(CHAR), value[1]};
  } else if (regex_match(value, regex(R"([0-9][0-9]*)"))) { // is int
    return {Type(INT), stoi(value)};
  } else if (regex_match(value, regex(R"([0-9][0-9]*\.[0-9][0-9]*)"))) { // is float
    return {Type(INT), stod(value)};
  } else if (value == "true" || value == "false") { // is bool
    return {Type(INT), value == "true" ? true : false};
  } else {
    // ERROR
    cerr << "ERROR in 'getVariableOrTemporaryVariable'"
         << "\n";
  }
}
