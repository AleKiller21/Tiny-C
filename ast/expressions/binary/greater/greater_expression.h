#ifndef GREATER_EXPRESSION
#define GREATER_EXPRESSION

#include "../relational_expression.h"

class greater_expression : public relational_expression
{
public:
    greater_expression(expression* expr1, expression* expr2, int position) : relational_expression(expr1, expr2, position, ">") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // GREATER_EXPRESSION