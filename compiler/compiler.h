#ifndef COMPILER
#define COMPILER

#include <list>
#include <iostream>
#include <string>
#include "../ast/declarations/external_declaration.h"

using namespace std;

class compiler
{
private:
    list<external_declaration*> source_code;

public:
    compiler(list<external_declaration*> source_code);
    void validate_semantic();
    string generate_code();
};

#endif // COMPILER