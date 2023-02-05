#include <iostream>
#include <string>

#include "include/datas.h"
#include "include/cropaddon.h"

using namespace std;

CROP_COMPILE_CODE(CropProject project) {
    Function const *mainFunction;
    for (const auto &item: project.mainFile.functions) {
        if (item.name == "main") mainFunction = &item;
    }

    for (const auto &item: mainFunction->codes) {
        if (item.type == EXECUTE_FUNCTION) {
            if (item.functionName == "println") {
                auto str = any_cast<string>(item.arguments[0]);
                cout << str.substr(1, str.size() - 2) << "\n";
            }
        }
    }
}