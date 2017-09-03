#ifndef COMPILER
#define COMPILER

#include <list>
#include <iostream>
#include <string>
#include <map>
#include "../ast/declarations/external_declaration.h"
#include "../redundancy_manager/redundancy_manager.h"

using namespace std;

extern int declaration_pos;
extern int declarator_pos;
extern redundancy_manager redund_manager;

class compiler
{
private:
    list<external_declaration*> source_code;

public:
    compiler(list<external_declaration*> source_code);
    void validate_semantic();
    void remove_unnecessary_nodes();
    string generate_code();
};

#endif // COMPILER