#ifndef LOGICAL_OR_EXPRESSION
#define LOGICAL_OR_EXPRESSION

#include "../relational_expression.h"

class logical_or_expression : public relational_expression
{
public:
    logical_or_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, "||") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // LOGICAL_OR_EXPRESSION