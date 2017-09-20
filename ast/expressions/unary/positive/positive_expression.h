#ifndef POSITIVE_EXPRESSION
#define POSITIVE_EXPRESSION

#include "../unary_expression.h"

class positive_expression : public unary_expression
{
public:
    positive_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // POSITIVE_EXPRESSION