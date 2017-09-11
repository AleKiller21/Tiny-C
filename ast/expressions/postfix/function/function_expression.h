#ifndef FUNCTION_EXPRESSION
#define FUNCTION_EXPRESSION

#include "../../expression.h"
#include "../../primary/id/id_expression.h"
#include "../../../declarations/function/function_declarator.h"
#include "../../expression_list/expression_list.h"
#include <vector>

class function_expression : public expression
{
private:
    expression* id;
    expression* arguments;

public:
    function_expression(expression* id, expression* arguments, int position) : expression(position)
    {
        this->id = id;
        this->arguments = arguments;
        lvalue = false;
    }
    
    string to_string();
    int get_kind();
    // string generate_mips();
    id_attributes get_type();
};

#endif // FUNCTION_EXPRESSION