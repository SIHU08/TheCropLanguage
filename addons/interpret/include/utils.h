#include <string>
#include <any>

using namespace std;

string to_string(any value);

vector<string> splitWithRegex(string s, const string& pattern = " ");