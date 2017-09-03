#ifndef ARRAY_DECLARATOR
#define ARRAY_DECLARATOR

#include "../declarator.h"
#include "../../expressions/expression.h"

class array_declarator : public declarator
{
private:
    expression* index_expr;
    bool validate_initialization();

public:
    array_declarator(int position, string* id, expression* index) : declarator(id, position)
    {
        index_expr = index;
    }

    string to_string();
    // string generate_mips();
    bool has_range();
    void validate_semantic();
};

#endif // ARRAY_DECLARATOR