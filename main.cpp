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
        string content = readFile(dir + "/src/" + filePath);
        sources.push_back(parse(filePath, content));
    }
    CropProject project = CropProject(parse(projectConfig.mainFile, readFile(dir + "/src/" + projectConfig.mainFile)), sources);

    for (DotCrop file : project.files) {
        file.parent = &project;
    }
    project.mainFile.parent = &project;

    doCompile(project, projectConfig.addonPath);
}
