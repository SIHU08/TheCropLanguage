#include <any>
#include <iostream>
#include <map>
#include <string>

#include "cropaddon.h"
#include "datas.h"
#include "variables.h"
#include "utils.h"

using namespace std;

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