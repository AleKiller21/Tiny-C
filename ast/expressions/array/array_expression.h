#ifndef ARRAY_EXPRESSION
#define ARRAY_EXPRESSION

#include "../expression.h"

class array_expression : public expression
{
private:
    expression* expr;
    expression* index;

public:
    array_expression(expression* expr, expression* index);
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // ARRAY_EXPRESSION