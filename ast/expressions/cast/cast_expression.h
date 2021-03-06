#ifndef CAST_EXPRESSION
#define CAST_EXPRESSION

#include "../expression.h"
#include "../../declarations/abstract_declarator.h"

class cast_expression : public expression
{
private:
    expression* expr;
    abstract_declarator* type;

public:
    cast_expression(abstract_declarator* type, expression* expr, int position) : expression(position)
    {
        this->expr = expr;
        this->type = type;
        lvalue = false;
    }

    string to_string();
    int get_kind();
    type_attributes get_type();
};

#endif // CAST_EXPRESSION