#ifndef PRE_DECREMENT_EXPRESSION
#define PRE_DECREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_decrement_expression : public unary_expression
{
public:
    pre_decrement_expression(expression* expr, int position) : unary_expression(expr, position) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // PRE_DECREMENT_EXPRESSION