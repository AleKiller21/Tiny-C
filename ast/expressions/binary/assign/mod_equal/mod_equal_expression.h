#ifndef MOD_EQUAL_EXPRESSION
#define MOD_EQUAL_EXPRESSION

#include "../assignment_expression.h"

class mod_equal_expression : public assignment_expression
{
public:
    mod_equal_expression(expression* expr1, expression* expr2, int position) : assignment_expression(expr1, expr2, position) {}

    string to_string();
    //string generate_mips();
};

#endif // MOD_EQUAL_EXPRESSION