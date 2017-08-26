#ifndef POINTER_EXPRESSION
#define POINTER_EXPRESSION

#include "../unary_expression.h"

class pointer_expression : public unary_expression
{
public:
    pointer_expression(expression* expr) : unary_expression(expr) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // POINTER_EXPRESSION