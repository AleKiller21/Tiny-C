#ifndef MULT_EXPRESSION
#define MULT_EXPRESSION

#include "../binary_expression.h"
#include "../multiplicative_expression.h"

class mult_expression : public multiplicative_expression
{
public:
    mult_expression(expression* expr1, expression* expr2, int position) : multiplicative_expression(expr1, expr2, position, "*") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // MULT_EXPRESSION