#ifndef RAND_EXPRESSION
#define RAND_EXPRESSION

#include "../unary_expression.h"

class rand_expression : public unary_expression
{
public:
    rand_expression(expression *expr, int position) : unary_expression(expr, position) { is_code = true; }

    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // RAND_EXPRESSION