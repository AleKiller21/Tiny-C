#ifndef DIV_EXPRESSION
#define DIV_EXPRESSION

#include "../multiplicative_expression.h"

class div_expression : public multiplicative_expression
{
public:
    div_expression(expression* expr1, expression* expr2, int position) : multiplicative_expression(expr1, expr2, position, "/") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // DIV_EXPRESSION