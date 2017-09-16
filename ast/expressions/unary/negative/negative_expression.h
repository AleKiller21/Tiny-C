#ifndef NEGATIVE_EXPRESSION
#define NEGATIVE_EXPRESSION

#include "../unary_expression.h"

class negative_expression : public unary_expression
{
public:
    negative_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    id_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // NEGATIVE_EXPRESSION