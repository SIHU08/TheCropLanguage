#include <any>
#include <cstdlib>
#include <regex>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

#include "../code/datas.h"
#include "../utils.h"
#include "parser_utility.h"

DotCrop parse(string body) {
  vector<string> imports;
  vector<Function> functions;
  int pointer = 0;

  string text;

  while (pointer < body.size()) {
    text += body[pointer];

    if (regex_match(trim(text), importReg)) {
      vector<string> splitted = split(text, '(');
      string argument = splitted[1].substr(1, splitted[1].size() - 3);
      imports.push_back(argument);
      text = "";
    } if (regex_match(trim(text), funcReg)) {
      vector<string> splitted = split(text, ' ');
      Type returnType = getType(splitted[0]);

      string functionName = splitted[1].substr(0, splitted[1].size() - 1);

      vector<Parameter> parameters;
      tie(pointer, parameters) = parseParameter(body, pointer);

      vector<Code> codeBlock;
      tie(pointer, codeBlock) = parseCodeBlock(body, pointer);

      text = "";

      Function func = Function(returnType, functionName, codeBlock);
      functions.emplace_back(func);
    }

    pointer++;
  }

  return DotCrop("test", imports, functions);
}
