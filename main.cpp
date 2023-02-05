#include <iostream>
#include <fstream>
#include <string>

#include "src/parser/code_parser.cpp"

using namespace std;

int main() {
    string path = "tests/helloworld.crop";

    ifstream openFile(path.data());
    string code;
	if( openFile.is_open() ){
		string line;
		while(getline(openFile, line)){
			code += line += "\n";
		}
		openFile.close();
	}


    Code parsed = parseCode(code);
}
