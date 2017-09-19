#ifndef OR_EXPRESSION
#define OR_EXPRESSION

#include "../bit_operator.h"

class or_expression : public bit_operator
{
public:
    or_expression(expression* expr1, expression* expr2, int position) : bit_operator(expr1, expr2, position, "|") {}

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // OR_EXPRESSION