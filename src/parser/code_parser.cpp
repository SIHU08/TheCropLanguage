#include <string>
#include <regex>
#include <vector>
#include <tuple>
#include <any>

#include "../datas.h"
#include "../utils.cpp"

regex funcReg(R"([A-Za-z]*\s\s*[A-Za-z][A-Za-z]*\s*\()");
regex callFuncReg(R"([A-Za-z][A-Za-z]*\s*\(.*\))");

tuple<int, vector<Parameter>> parseParameter(string body, int pointer) {
    vector<Parameter> parameters;

    pointer++;
    string text;
    while (pointer < body.size()) {
        if (body[pointer] == ')') break;

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
            if (body[pointer] == '}') break;

            if (body[pointer] != '\n') text += body[pointer];
            else if (!text.empty()) {
                text = trim(text);

                if (regex_match(text, callFuncReg)) {
                    vector<string> splitted = split(text, '(');
                    string func = splitted[0];
                    string argumentStr = splitted[1].substr(0, splitted[1].size() - 1);
                    vector<string> arguments = splitWithRegex(argumentStr, R"(,(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$))");
                    vector<any> args;
                    for (const auto &item: arguments) {
                        args.emplace_back(item);
                    }

                    Code code(func, args);

                    codes.emplace_back(code);
                }

                text = "";
            }
        }

        if (body[pointer] == '{') isStarted = true;
        pointer++;
    }
    return make_tuple(pointer, codes);
}

DotCrop parse(string body) {
    vector<Function> functions;
    int pointer = 0;

    string text;

    while (pointer < body.size()) {
        text += body[pointer];

        if (regex_match(text, funcReg)) {
            vector<string> splitted = split(text, ' ');
            Type returnType(VariableType::VOID);
            if (splitted[0] == "void") returnType = Type(VariableType::VOID);
            else if (splitted[0] == "int") returnType = Type(VariableType::INT);
            else if (splitted[0] == "float") returnType = Type(VariableType::FLOAT);
            else if (splitted[0] == "char") returnType = Type(VariableType::CHAR);
            else returnType = Type(splitted[0]);

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

    return DotCrop("test", vector<string>(), functions);
}