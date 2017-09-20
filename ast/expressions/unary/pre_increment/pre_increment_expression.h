#ifndef PRE_INCREMENT_EXPRESSION
#define PRE_INCREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_increment_expression : public unary_expression
{
public:
    pre_increment_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; is_code = true; }
    string to_string();
    int get_kind();
    type_attributes get_type();
    string *get_operand_id();
    asm_code *generate_code(stack_manager *manager);
};

#endif // PRE_INCREMENT_EXPRESSION