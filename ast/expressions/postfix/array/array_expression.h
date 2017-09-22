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
    asm_code *generate_array_expression_code(stack_manager *manager, string reg, string memory_access_operation = "load");
};

#endif // ARRAY_EXPRESSION