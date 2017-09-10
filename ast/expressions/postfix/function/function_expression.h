#ifndef FUNCTION_EXPRESSION
#define FUNCTION_EXPRESSION

#include "../../expression.h"

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
    }
    
    string to_string();
    int get_kind();
    // string generate_mips();
    id_attributes* get_type();
};

#endif // FUNCTION_EXPRESSION