#ifndef POST_DECREMENT_EXPRESSION
#define POST_DECREMENT_EXPRESSION

#include "../../expression.h"

class post_decrement_expression : public expression
{
private:
    expression* expr;

public:
    post_decrement_expression(expression* expr, int position) : expression(position)
    {
        this->expr = expr;
        lvalue = false;
        is_code = true;
    }
    
    string to_string();
    int get_kind();
    id_attributes get_type();
    string *get_operand_id();
    asm_code *generate_code(stack_manager *manager);
};

#endif // POST_DECREMENT_EXPRESSION