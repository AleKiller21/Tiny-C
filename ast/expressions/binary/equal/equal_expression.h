#ifndef EQUAL_EXPRESSION
#define EQUAL_EXPRESSION

#include "../relational_expression.h"

class equal_expression : public relational_expression
{
public:
    equal_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, "==") {}

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // EQUAL_EXPRESSION