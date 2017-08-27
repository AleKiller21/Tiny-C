#ifndef LSHIFT_EQUAL_EXPRESSION
#define LSHIFT_EQUAL_EXPRESSION

#include "../assignment_expression.h"

class lshift_equal_expression : public assignment_expression
{
public:
    lshift_equal_expression(expression* expr1, expression* expr2, int position) : assignment_expression(expr1, expr2, position) {}

    string to_string();
    //string generate_mips();
};

#endif // LSHIFT_EQUAL_EXPRESSION