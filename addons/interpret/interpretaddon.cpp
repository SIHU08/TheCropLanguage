#include <any>
#include <iostream>
#include <map>
#include <string>

#include "cropaddon.h"
#include "datas.h"
#include "exprtk.hpp"
#include "utils.h"
#include "variables.h"

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
  
  parser_t parser();
  parser.compile(expression_string, expression);

  return expression.value();
}

void callFunction(Function function) {
  map<string, Variable> variableMap;

  for (const auto &item : function.codes) {
    if (item.type == EXECUTE_FUNCTION) {
      if (item.functionName == "println") {
        string arg = any_cast<string>(item.functionArguments[0]);
        string text;
        if (arg[0] == '"' && arg[arg.size() - 1] == '"') {
          text = arg.substr(1, arg.size() - 2);
        } else {
          if (!variableMap.count(arg)) {
            //cout << calcExpression<double>(variableMap, arg) << "\n";
            cerr << "Variable '" << arg << "' NOT found." << "\n";
            continue;
          }

          text = to_string(getVariableValue(variableMap[arg]));
        }
        cout << text << "\n";
      }
    } else if (item.type == CREATE_VARIABLE) {
      variableMap[item.variableName] =
          Variable{item.variableType, item.variableData};
    } else if (item.type == UPDATE_VARIABLE) {
      variableMap[item.variableName] =
          Variable{item.variableType, item.variableData};
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