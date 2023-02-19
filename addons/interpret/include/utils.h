#include <any>
#include <string>

using namespace std;

string to_string(any value);

vector<string> splitWithRegex(string s, const string &pattern = " ");

string genRandomString(int len);

string trim(const string &s);