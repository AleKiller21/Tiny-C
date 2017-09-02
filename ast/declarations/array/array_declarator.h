#ifndef ARRAY_DECLARATOR
#define ARRAY_DECLARATOR

#include "../declarator.h"
#include "../../expressions/expression.h"

class array_declarator : public declarator
{
private:
    expression* index_expr;

public:
    array_declarator(int position, id_expression* id, expression* index) : declarator(id, position)
    {
        index_expr = index;
    }

    string to_string();
    // string generate_mips();
    void validate_semantic();
};

#endif // ARRAY_DECLARATOR