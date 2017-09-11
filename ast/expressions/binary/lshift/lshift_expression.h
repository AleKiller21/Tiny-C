#ifndef LSHIFT_EXPRESSION
#define LSHIFT_EXPRESSION

#include "../shift_expression.h"

class lshift_expression : public shift_expression
{
public:
    lshift_expression(expression* expr1, expression* expr2, int position) : shift_expression(expr1, expr2, position, "<<") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // LSHIFT_EXPRESSION