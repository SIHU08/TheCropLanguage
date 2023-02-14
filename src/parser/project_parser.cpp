#include <any>
#include <cstdlib>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

#include "../code/datas.h"
#include "../utils.h"
#include "parser_utility.h"

ProjectConfig parseProjectConfig(string body) {
  ProjectConfig config;
  int pointer = 0;

  string text;
  while (pointer < body.size()) {
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

        string arg = any_cast<string>(args[0]);
        arg = arg.substr(1, arg.size() - 2);
        if (func == "mainFile") {
          config.mainFile = arg;
        } else if (func == "addFile") {
          config.files.push_back(arg);
        } else if (func == "addon") {
          config.addonPath = arg;
        }
      }
      text = "";
    }
    pointer++;
  }

  return config;
}
