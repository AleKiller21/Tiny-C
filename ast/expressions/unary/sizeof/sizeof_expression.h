#ifndef SIZEOF_EXPRESSION
#define SIZEOF_EXPRESSION

#include "../unary_expression.h"
#include "../../../declarations/abstract_declarator.h"
#include "../../primary/id/id_expression.h"
#include "../../../declarations/array/array_declarator.h"

extern map<string, string> data_section;

class sizeof_expression : public unary_expression
{
private:
    abstract_declarator* type;

public:
    sizeof_expression(expression* expr, abstract_declarator* type, int position) : unary_expression(expr, position)
    {
        this->type = type;
        lvalue = false;
        is_code = false;
    }

    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // SIZEOF_EXPRESSION