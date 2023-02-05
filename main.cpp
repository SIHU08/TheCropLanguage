#include <iostream>
#include <fstream>
#include <string>

#include "src/parser/code_parser.cpp"
#include "src/compileraddon/addon_loader.cpp"

using namespace std;

int main(int argc, char **argv) {
    string path = argv[1];

    ifstream openFile(path.data());
    string code;
    if (openFile.is_open()) {
        string line;
        while (getline(openFile, line)) {
            code += line += "\n";
        }
        openFile.close();
    }

    DotCrop mainDotCrop = parse(code);
    CropProject project = CropProject(mainDotCrop, vector<DotCrop>());

    doCompile(project);
}
