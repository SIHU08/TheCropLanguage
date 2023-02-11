#include <iostream>
#include <string>
#include <map>
#include <any>

#include "include/datas.h"
#include "include/cropaddon.h"

using namespace std;

CROP_COMPILE_CODE(CropProject project) {
    Function const *mainFunction;
    for (const auto &item: project.mainFile.functions) {
        if (item.name == "main") mainFunction = &item;
    }

    map<string, any> variableMap;

    for (const auto &item: mainFunction->codes) {
        if (item.type == EXECUTE_FUNCTION) {
            if (item.functionName == "println") {
                auto arg = any_cast<string>(item.functionArguments[0]);
                string text;
                if (arg[0] == '"' && arg[arg.size() - 1] == '"') {
                    text = arg.substr(1, arg.size() - 2);
                } else {
                    if (!variableMap.count(arg)) {
                        cerr << "Variable " << text << " NOT found.";
                        return;
                    }
                    text = any_cast<string>(variableMap[arg]);
                }
                cout << text << "\n";
            }
        } else if (item.type == CREATE_VARIABLE) {
            variableMap[item.variableName] = item.variableData;
        } else if (item.type == UPDATE_VARIABLE) {
            variableMap[item.variableName] = item.variableData;
        }
    }
}