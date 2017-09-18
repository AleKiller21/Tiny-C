#ifndef LESS_EQUAL_EXPRESSION
#define LESS_EQUAL_EXPRESSION

#include "../relational_expression.h"

class less_equal_expression : public relational_expression
{
public:
    less_equal_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, "<=") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // LESS_EQUAL_EXPRESSION