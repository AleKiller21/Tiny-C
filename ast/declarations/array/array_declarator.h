#ifndef ARRAY_DECLARATOR
#define ARRAY_DECLARATOR

#include "../declarator.h"
#include "../../expressions/expression.h"

class array_declarator : public declarator
{
private:
    declarator* decl;
    expression* index_expr;

public:
    array_declarator(int position, declarator* decl, expression* index) : declarator(position)
    {
        this->decl = decl;
        index_expr = index;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // ARRAY_DECLARATOR