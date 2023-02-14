#include <iostream>
#include <fstream>
#include <string>

#include "src/parser/code_parser.cpp"
#include "src/parser/project_parser.cpp"
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

    ProjectConfig projectConfig = parseProjectConfig(code);

    vector<DotCrop> sources;
    for (string filePath : projectConfig.files) {
        sources.push_back(parse(filePath));
    }
    CropProject project = CropProject(parse(projectConfig.mainFile), sources);

    doCompile(project, projectConfig.addonPath);
}
