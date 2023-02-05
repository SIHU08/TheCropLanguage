#ifndef CROP_DATA_H
#define CROP_DATA_H

#include <string>
#include <utility>
#include <vector>
#include <any>

using namespace std;

typedef struct {
    vector<string> name;
} Parameter;

typedef struct {
    string name;
    any value;
} Variable;

enum VariableType {
    VOID, INT, FLOAT, CHAR, OBJECT
};

class Type {
public:
    explicit Type(VariableType type) : type(type) {}

    explicit Type(string objName) : objName(std::move(objName)) { type = OBJECT; }

    VariableType type;
    string objName;
};

enum CodeType {
    EXECUTE_FUNCTION,
};

class Code {
public:
    Code(string functionName, const vector<any> &arguments) : functionName(std::move(functionName)),
                                                              arguments(arguments) { type = EXECUTE_FUNCTION; }

    CodeType type;
    vector<any> arguments;
    string functionName;
};

class Function {
public:
    Function(Type returnType, string name, const vector<Code> &codes) : returnType(std::move(returnType)),
                                                                        name(std::move(name)), codes(codes) {}

    Type returnType;
    string name;
    vector<Code> codes;
};

class DotCrop {
public:
    DotCrop(string aPackage, const vector<string> &imports, const vector<Function> &functions) : package(std::move(
            aPackage)), imports(imports), functions(functions) {}

    string package;
    vector<string> imports;
    vector<Function> functions;
};

class CropProject {
public:
    CropProject(DotCrop mainFile, const vector<DotCrop> &files) : mainFile(std::move(mainFile)), files(files) {}

    DotCrop mainFile;
    vector<DotCrop> files;
};

#endif //CROP_DATA_H