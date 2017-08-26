#ifndef FUNCTION_EXPRESSION
#define FUNCTION_EXPRESSION

#include "../expression.h"

class function_expression : public expression
{
private:
    expression* id;
    expression* arguments;

public:
    function_expression(expression* id, expression* arguments);
    string to_string();
    // string generate_mips();
    // string get_type();
};

#endif // FUNCTION_EXPRESSION