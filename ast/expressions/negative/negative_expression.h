#ifndef NEGATIVE_EXPRESSION
#define NEGATIVE_EXPRESSION

#include "../unary_expression.h"

class negative_expression : public unary_expression
{
public:
    negative_expression(expression* expr) : unary_expression(expr) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // NEGATIVE_EXPRESSION