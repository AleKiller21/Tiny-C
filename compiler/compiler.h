#ifndef COMPILER
#define COMPILER

#include <list>
#include <iostream>
#include <string>
#include <map>
#include "../ast/declarations/external_declaration.h"

using namespace std;

extern int declaration_pos;
extern int declarator_pos;

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