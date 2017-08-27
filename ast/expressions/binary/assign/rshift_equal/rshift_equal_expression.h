#ifndef RSHIFT_EQUAL_EXPRESSION
#define RSHIFT_EQUAL_EXPRESSION

#include "../assignment_expression.h"

class rshift_equal_expression : public assignment_expression
{
public:
    rshift_equal_expression(expression* expr1, expression* expr2, int position) : assignment_expression(expr1, expr2, position) {}

    string to_string();
    //string generate_mips();
};

#endif // RSHIFT_EQUAL_EXPRESSION