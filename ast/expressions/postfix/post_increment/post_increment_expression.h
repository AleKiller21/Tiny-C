#ifndef POST_INCREMENT_EXPRESSION
#define POST_INCREMENT_EXPRESSION

#include "../../expression.h"

class post_increment_expression : public expression
{
private:
    expression* expr;

public:
    post_increment_expression(expression* expr, int position) : expression(position)
    {
        this->expr = expr;
        lvalue = false;
        is_code = true;
    }
    
    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
    string *get_operand_id();
};

#endif // POST_INCREMENT_EXPRESSION