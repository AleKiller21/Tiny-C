#ifndef SRAND_EXPRESSION
#define SRAND_EXPRESSION

#include "../unary_expression.h"

class srand_expression : public unary_expression
{
public:
    srand_expression(expression *expr, int position) : unary_expression(expr, position) { is_code = true; }

    string to_string();
    int get_kind();
    id_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // SRAND_EXPRESSION