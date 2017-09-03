#ifndef POINTER_EXPRESSION
#define POINTER_EXPRESSION

#include "../unary_expression.h"

class pointer_expression : public unary_expression
{
public:
    pointer_expression(expression* expr, int position) : unary_expression(expr, position) {}
    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // POINTER_EXPRESSION