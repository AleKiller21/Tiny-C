#ifndef LOGICAL_AND_EXPRESSION
#define LOGICAL_AND_EXPRESSION

#include "../relational_expression.h"

class logical_and_expression : public relational_expression
{
public:
    logical_and_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, "&&") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // LOGICAL_AND_EXPRESSION