#ifndef PRINTF_EXPRESSION
#define PRINTF_EXPRESSION

#include "../unary_expression.h"

class printf_expression : public unary_expression
{
public:
    printf_expression(expression* args, int position) : unary_expression(args, position) {}
    string to_string();
    // string generate_mips();
    // string get_type();
};

#endif // PRINTF_EXPRESSION