#ifndef NEGATION_EXPRESSION
#define NEGATION_EXPRESSION

#include "../unary_expression.h"

class negation_expression : public unary_expression
{
public:
    negation_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    id_attributes get_type();
    // string generate_mips();
};

#endif // NEGATION_EXPRESSION