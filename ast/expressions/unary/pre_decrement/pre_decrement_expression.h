#ifndef PRE_DECREMENT_EXPRESSION
#define PRE_DECREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_decrement_expression : public unary_expression
{
public:
    pre_decrement_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; is_code = true;}
    string to_string();
    int get_kind();
    id_attributes get_type();
    string *get_operand_id();
    asm_code *generate_code(stack_manager *manager);
};

#endif // PRE_DECREMENT_EXPRESSION