#ifndef RSHIFT_EXPRESSION
#define RSHIFT_EXPRESSION

#include "../shift_expression.h"

class rshift_expression : public shift_expression
{
public:
    rshift_expression(expression* expr1, expression* expr2, int position) : shift_expression(expr1, expr2, position, ">>") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // RSHIFT_EXPRESSION