#ifndef LESS_EXPRESSION
#define LESS_EXPRESSION

#include "../relational_expression.h"

class less_expression : public relational_expression
{
public:
    less_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, "<") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // LESS_EXPRESSION