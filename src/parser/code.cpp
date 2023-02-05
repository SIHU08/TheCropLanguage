#include <string>
#include <vector>

using namespace std;

typedef struct {
    string name;
} Function;

typedef struct {
    string name;
} Variable;

typedef struct {
    string package;
    vector<string> imports;
    vector<Function> functions;
} Code;