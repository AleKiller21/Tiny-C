#ifndef SIMPLE_DECLARATOR
#define SIMPLE_DECLARATOR

#include "../declarator.h"
#include "../../expressions/primary/id/id_expression.h"
#include <iostream>

class simple_declarator : public declarator
{
private:
    bool validate_existance(string id, symbol* sym);
    bool validate_initialization();

public:
    simple_declarator(id_expression* id, int position) : declarator(id, position) {}

    string to_string();
    // stirng generate_mips();
    void validate_semantic();
};

#endif // SIMPLE_DECLARATOR