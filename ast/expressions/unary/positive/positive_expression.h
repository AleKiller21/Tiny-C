#ifndef POSITIVE_EXPRESSION
#define POSITIVE_EXPRESSION

#include "../unary_expression.h"

class positive_expression : public unary_expression
{
public:
    positive_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    id_attributes get_type();
    // string generate_mips();
};

#endif // POSITIVE_EXPRESSION