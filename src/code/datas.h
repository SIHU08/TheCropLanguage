#ifndef CROP_DATA_H
#define CROP_DATA_H

#include <any>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum VariableType {
    VOID, INT, FLOAT, CHAR, BOOL, OBJECT
};

class Type {
public:
    explicit Type() : type(VOID) {}

    explicit Type(VariableType type) : type(type) {}

    explicit Type(string objName) : objName(std::move(objName)) { type = OBJECT; }

    VariableType type;
    string objName;

    bool operator==(const Type &other) const {
        return type == other.type;
    }

    bool operator!=(const Type &other) const {
        return type != other.type;
    }
};

typedef struct {
    vector<string> name;
} Parameter;

typedef struct {
    Type type;
    any value;
} Variable;


class Function;

class DotCrop;

class CropProject;

#define EXECUTE_FUNCTION 0
#define CREATE_VARIABLE 1
#define UPDATE_VARIABLE 2
#define IF_STATEMENT 3
class Code {
public:
    Code(string functionName, const vector<any> &functionArguments)
            : functionName(std::move(functionName)),
              functionArguments(functionArguments) {
        type = EXECUTE_FUNCTION;
    }

    Code(Type variableType, string variableName, any variableData)
            : variableType(std::move(variableType)),
              variableName(std::move(variableName)),
              variableData(std::move(variableData)) {
        type = CREATE_VARIABLE;
    }

    Code(string variableName, any variableData)
            : variableName(std::move(variableName)),
              variableData(std::move(variableData)) {
        type = UPDATE_VARIABLE;
    }

    Code(const string &statement, const vector<Code> &ifCodeBlock, const vector<Code> &elseCodeBlock = vector<Code>())
            : statement(
            statement), ifCodeBlock(ifCodeBlock), elseCodeBlock(elseCodeBlock) {
        type = IF_STATEMENT;
    }

    Function *parent = nullptr;
    int type;
    string functionName;
    vector<any> functionArguments;
    Type variableType;
    string variableName;
    any variableData;
    string statement;
    vector<Code> ifCodeBlock;
    vector<Code> elseCodeBlock;
};

class Function {
public:
    Function(Type returnType, string name, const vector<Code> &codes)
            : returnType(std::move(returnType)), name(std::move(name)), codes(codes) {
    }

    Type returnType;
    string name;
    vector<Code> codes;
    DotCrop *parent = nullptr;
};

class DotCrop {
public:
    DotCrop(const string &name, const vector<string> &imports, const vector<Function> &functions) : name(name),
                                                                                                    imports(imports),
                                                                                                    functions(
                                                                                                            functions) {}

    string name;
    vector<string> imports;
    vector<Function> functions;
    CropProject *parent = nullptr;

    bool isImported(DotCrop other) {
        for (string importStr: imports) {
            if (importStr == other.name) {
                return true;
            }
        }
        return false;
    }
};

class CropProject {
public:
    CropProject(DotCrop mainFile, const vector<DotCrop> &files)
            : mainFile(std::move(mainFile)), files(files) {}

    DotCrop mainFile;
    vector<DotCrop> files;
};

typedef struct {
    string mainFile;
    vector<string> files;
    string addonPath;
} ProjectConfig;

#endif // CROP_DATA_H