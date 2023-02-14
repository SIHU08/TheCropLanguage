#ifndef CROP_UTILITY_H
#define CROP_UTILITY_H

#include <vector>
#include <sstream>
#include <regex>

using namespace std;

#define WHITESPACE " \n\r\t\f\v"

vector<string> split(const string &input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

vector<string> splitWithRegex(string s, const string& pattern = " ") {
    regex re(pattern);
    sregex_token_iterator it(s.begin(), s.end(), re, -1), end;
    vector<string> answer(it, end);
    return answer;
}

string ltrim(const string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {
    return rtrim(ltrim(s));
}

#endif // CROP_UTILITY_H