#ifndef AND_EXPRESSION
#define AND_EXPRESSION

#include "../bit_operator.h"

class and_expression : public bit_operator
{
public:
    and_expression(expression* expr1, expression* expr2, int position) : bit_operator(expr1, expr2, position, "&") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // AND_EXPRESSION