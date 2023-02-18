#include <iostream>
#include <fstream>
#include <string>

#include "src/parser/code_parser.cpp"
#include "src/parser/project_parser.cpp"
#include "src/compileraddon/addon_loader.cpp"

using namespace std;

string readFile(string path) {
    ifstream openFile(path.data());
    string content;
    if (openFile.is_open()) {
        string line;
        while (getline(openFile, line)) {
            content += line += "\n";
        }
        openFile.close();
    }
    return content;
}

int main(int argc, char **argv) {
    string path = argv[1];
    string code = readFile(path);

    ProjectConfig projectConfig = parseProjectConfig(code);

    string dir = path.substr(0, path.find_last_of("/\\"));

    vector<DotCrop> sources;
    for (const string& filePath: projectConfig.files) {
        string content = readFile(dir + "/" + filePath);
        cout << content << "\n";
        sources.push_back(parse(content));
    }
    CropProject project = CropProject(parse(readFile(dir + "/" + projectConfig.mainFile)), sources);

    doCompile(project, projectConfig.addonPath);
}
