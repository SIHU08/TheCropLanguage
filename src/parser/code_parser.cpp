#include <string>
#include <regex>
#include <vector>
#include <iostream>

#include "code.cpp"
#include "../utils.cpp"

regex functionRegex("([A-Za-z]*\\s\\s*[A-Za-z][A-Za-z]*\\s*)");

Code parseCode(string body) {
    vector<Function> functions;
    int pointer = 0;

    string text;

    while (pointer < body.size()) {
        text += body[pointer];

        cout << text << "\n";
        
        if (regex_match(text, functionRegex)) {
            vector<string> splitted = split(text, ' ');
            string returnType = splitted[0];
            string functionName = splitted[1];

            cout << "Return Type: " << returnType << " / Name: " << functionName << "\n";
        }

        pointer++;
    }

    return {"test", vector<string>(), functions};
}