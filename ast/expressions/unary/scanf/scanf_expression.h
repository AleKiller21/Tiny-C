#ifndef SCANF_EXPRESSION
#define SCANF_EXPRESSION

#include "../unary_expression.h"

class scanf_expression : public unary_expression
{
public:
    scanf_expression(expression* args, int position) : unary_expression(args, position) {}
    string to_string();
    // string generate_mips();
    // string get_type();
};

#endif // SCANF_EXPRESSION