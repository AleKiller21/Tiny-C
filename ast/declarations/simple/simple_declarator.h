#ifndef SIMPLE_DECLARATOR
#define SIMPLE_DECLARATOR

#include "../declarator.h"
#include "../../expressions/primary/id/id_expression.h"
#include "../../expressions/binary/assign/assignment_expression.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

class simple_declarator : public declarator
{
private:
    bool validate_initialization();

public:
    simple_declarator(string* id, int position) : declarator(id, position, SIMPLE) {}

    string to_string();
    // stirng generate_mips();
    void validate_semantic();
    static bool validate_init_expression(id_attributes decl_type, expression* expr, int decl_position);
};

#endif // SIMPLE_DECLARATOR