#include <any>
#include <map>

#include "datas.h"

any getVariableValue(Variable variable);
Variable getVariableOrTemporaryVariable(string value,
                                        map<string, Variable> variableMap);