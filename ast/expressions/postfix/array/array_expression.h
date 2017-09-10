#ifndef ARRAY_EXPRESSION
#define ARRAY_EXPRESSION

#include "../../expression.h"

class array_expression : public expression
{
private:
    expression* expr;
    expression* index;

public:
    array_expression(expression* expr, expression* index, int position) : expression(position)
    {
        this->expr = expr;
        this->index = index;
        lvalue = true;
    }

    string to_string();
    int get_kind();
    id_attributes get_type();
    // string generate_mips();
};

#endif // ARRAY_EXPRESSION