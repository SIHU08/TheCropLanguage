#include <any>
#include <string>
#include <iostream>

#include "datas.h"
#include "cropaddon.h"

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
    cerr << "e guo sse nun sa ram da zuk er" << "\n";
    exit(1);
  } else {
    cerr << "WTF" << "\n";
    exit(1);
  }
  return nullptr;
}
