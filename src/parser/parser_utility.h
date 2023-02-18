#ifndef CROP_PARSER_UTILITY_H
#define CROP_PARSER_UTILITY_H

#include <any>
#include <cstdlib>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

#include "../code/datas.h"
#include "../utils.h"

regex funcReg(R"([A-Za-z][A-Za-z]*\s\s*[A-Za-z][A-Za-z]*\s*\()");
regex callFuncReg(R"([A-Za-z][A-Za-z]*\s*\(.*\))");
regex createVariableReg(R"([A-Za-z][A-Za-z]*\s\s*[A-Za-z][A-Za-z]*\s*=\s*.*)");
regex updateVariableReg(R"([A-Za-z][A-Za-z]*\s*=\s*.*)");
regex importReg(R"(import\("[a-zA-Z-_][a-zA-Z-_]*.crop"\))");

Type getType(string text) {
  if (text == "void")
    return Type(VOID);
  else if (text == "int")
    return Type(INT);
  else if (text == "float")
    return Type(FLOAT);
  else if (text == "char")
    return Type(CHAR);
  else if (text == "bool")
    return Type(BOOL);
  else
    return Type(text);
}

any castValue(Type type, string v) {
  switch (type.type) {
  case VOID:
    return nullptr;
  case INT:
    return stoi(v);
  case FLOAT:
    return stod(v);
  case CHAR:
    return v[1];
  case BOOL:
    return v == "true" ? true : false;
  case OBJECT:
    return nullptr; // TODO
  }
  return nullptr;
}

tuple<int, vector<Parameter>> parseParameter(string body, int pointer) {
  vector<Parameter> parameters;

  pointer++;
  string text;
  while (pointer < body.size()) {
    if (body[pointer] == ')')
      break;

    text += body[pointer];

    pointer++;
  }
  return make_tuple(pointer, parameters);
}

tuple<int, vector<Code>> parseCodeBlock(string body, int pointer) {
  vector<Code> codes;

  string text;
  bool isStarted = false;
  while (pointer < body.size()) {
    if (isStarted) {
      if (body[pointer] == '}')
        break;

      if (body[pointer] != '\n')
        text += body[pointer];
      else if (!text.empty()) {
        text = trim(text);

        if (regex_match(text, callFuncReg)) { // Call Function
          vector<string> splitted = split(text, '(');
          string func = splitted[0];
          string argumentStr = splitted[1].substr(0, splitted[1].size() - 1);
          vector<string> arguments = splitWithRegex(
              argumentStr, R"(,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$))");
          vector<any> args;
          for (const auto &item : arguments) {
            args.emplace_back(item);
          }

          Code code(func, args);
          codes.emplace_back(code);
        } else if (regex_match(text, createVariableReg)) { // Create Variable
          vector<string> splitted = split(text, ' ');
          Type type = getType(splitted[0]);
          string name = splitted[1];
          string value = splitted[3];

          Code code(type, name, castValue(type, value));
          codes.emplace_back(code);
        } else if (regex_match(text, updateVariableReg)) { // Update Variable
          vector<string> splitted = split(text, ' ');
          string name = splitted[0];
          string value = splitted[2];

          Code code(name, value);
          codes.emplace_back(code);
        }
        text = "";
      }
    }

    if (body[pointer] == '{')
      isStarted = true;
    pointer++;
  }
  return make_tuple(pointer, codes);
}

#endif // CROP_PARSER_UTILITY_H