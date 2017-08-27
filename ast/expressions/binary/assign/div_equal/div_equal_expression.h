#ifndef DIV_EQUAL_EXPRESSION
#define DIV_EQUAL_EXPRESSION

#include "../assignment_expression.h"

class div_equal_expression : public assignment_expression
{
public:
    div_equal_expression(expression* expr1, expression* expr2, int position) : assignment_expression(expr1, expr2, position) {}

    string to_string();
    //string generate_mips();
};

#endif // DIV_EQUAL_EXPRESSION