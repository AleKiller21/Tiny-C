#ifndef POSITIVE_EXPRESSION
#define POSITIVE_EXPRESSION

#include "../unary_expression.h"

class positive_expression : public unary_expression
{
public:
    positive_expression(expression* expr) : unary_expression(expr) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // POSITIVE_EXPRESSION