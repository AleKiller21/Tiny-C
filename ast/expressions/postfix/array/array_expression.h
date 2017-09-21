#ifndef ARRAY_EXPRESSION
#define ARRAY_EXPRESSION

#include "../../expression.h"
#include "../../primary/id/id_expression.h"

extern map<string, string> data_section;

class array_expression : public expression
{
private:
    expression* expr;
    expression* index;

    string load_base_address(stack_manager *manager);

public:
    array_expression(expression* expr, expression* index, int position) : expression(position)
    {
        this->expr = expr;
        this->index = index;
        lvalue = true;
        is_code = true;
    }

    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // ARRAY_EXPRESSION