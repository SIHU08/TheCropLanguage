#include <any>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include "cropaddon.h"
#include "datas.h"
#include "exprtk.hpp"
#include "utils.h"
#include "variables.h"

regex statementEqualsReg(R"([A-Za-z][A-Za-z]*\s\s*==\s\s*.*)");
regex statementNotEqualsReg(R"([A-Za-z][A-Za-z]*\s\s*!=\s\s*.*)");
regex statementLessThanOrEqualsReg(R"([A-Za-z][A-Za-z]*\s\s*<=\s\s*.*)");
regex statementLessThanReg(R"([A-Za-z][A-Za-z]*\s\s*<\s\s*.*)");
regex statementGreaterThanOrEqualsReg(R"([A-Za-z][A-Za-z]*\s\s*>=\s\s*.*)");
regex statementGreaterThanReg(R"([A-Za-z][A-Za-z]*\s\s*>\s\s*.*)");

using namespace std;

template <typename T>
T calcExpression(map<string, Variable> variableMap,
                 string expression_string) { // TODO
  typedef exprtk::symbol_table<T> symbol_table_t;
  typedef exprtk::expression<T> expression_t;
  typedef exprtk::parser<T> parser_t;

  symbol_table_t symbol_table;
  for (const auto &item : variableMap) {
    symbol_table.add_constant(item.first, any_cast<int>(item.second.value));
  }

  expression_t expression;
  expression.register_symbol_table(symbol_table);

  parser_t parser;
  parser.compile(expression_string, expression);

  return expression.value();
}

void callFunction(const Function &function) {
  map<string, Variable> variableMap;

  for (const auto &item : function.codes) {
    if (item.type == EXECUTE_FUNCTION) {
      if (item.functionName == "println") {
        auto arg = any_cast<string>(item.functionArguments[0]);
        string text = to_string(
            getVariableValue(getVariableOrTemporaryVariable(arg, variableMap)));
        cout << text << "\n";
      }
    } else if (item.type == CREATE_VARIABLE) {
      variableMap[item.variableName] =
          Variable{item.variableType, item.variableData};
    } else if (item.type == UPDATE_VARIABLE) {
      variableMap[item.variableName] =
          Variable{item.variableType, item.variableData};
    } else if (item.type == IF_STATEMENT) {
      string st = item.statement;
      vector<string> arguments = splitWithRegex(
          st, R"(==|!=|>=|<=|>|<(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$))");
      Variable leftTerm =
                   getVariableOrTemporaryVariable(arguments[0], variableMap),
               rightTerm =
                   getVariableOrTemporaryVariable(arguments[1], variableMap);
      any left = getVariableValue(leftTerm),
          right = getVariableValue(rightTerm);
      bool isTrue;
      if (left.type() != right.type()) {
        cerr << "Type is incorrect";
        return;
      }

      if (regex_match(st, statementEqualsReg)) {
        isTrue = to_string(left) == to_string(right);
      } else if (regex_match(st, statementNotEqualsReg)) {
        isTrue = to_string(left) != to_string(right);
      } else if (regex_match(st, statementLessThanOrEqualsReg)) {
        if (leftTerm.type.type == INT)
          isTrue = stoi(to_string(left)) <= stoi(to_string(right));
        else if (leftTerm.type.type == FLOAT)
          isTrue = stod(to_string(left)) <= stod(to_string(right));
        else {
          cerr << "Type is incorrect";
          return;
        }
      } else if (regex_match(st, statementLessThanReg)) {
        if (leftTerm.type.type == INT)
          isTrue = stoi(to_string(left)) < stoi(to_string(right));
        else if (leftTerm.type.type == FLOAT)
          isTrue = stod(to_string(left)) < stod(to_string(right));
        else {
          cerr << "Type is incorrect";
          return;
        }
      } else if (regex_match(st, statementGreaterThanOrEqualsReg)) {
        if (leftTerm.type.type == INT)
          isTrue = stoi(to_string(left)) >= stoi(to_string(right));
        else if (leftTerm.type.type == FLOAT)
          isTrue = stod(to_string(left)) >= stod(to_string(right));
        else {
          cerr << "Type is incorrect";
          return;
        }
      } else if (regex_match(st, statementGreaterThanReg)) {
        if (leftTerm.type.type == INT)
          isTrue = stoi(to_string(left)) > stoi(to_string(right));
        else if (leftTerm.type.type == FLOAT)
          isTrue = stod(to_string(left)) > stod(to_string(right));
        else {
          cerr << "Type is incorrect";
          return;
        }
      }

      if (isTrue) {
        callFunction(Function(Type(), genRandomString(8), item.codeBlock));
      }
    }
  }
}

CROP_COMPILE_CODE(CropProject project) {
  Function const *mainFunction;
  for (const auto &item : project.mainFile.functions) {
    if (item.name == "main")
      mainFunction = &item;
  }

  callFunction(*mainFunction);
}