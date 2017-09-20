#ifndef TIME_EXPRESSION
#define TIME_EXPRESSION

#include "../unary_expression.h"

class time_expression : public unary_expression
{
public:
    time_expression(expression *expr, int position) : unary_expression(expr, position) { is_code = true; }

    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // TIME_EXPRESSION