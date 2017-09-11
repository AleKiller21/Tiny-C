#ifndef PRE_DECREMENT_EXPRESSION
#define PRE_DECREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_decrement_expression : public unary_expression
{
public:
    pre_decrement_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    id_attributes get_type();
    // string generate_mips();
};

#endif // PRE_DECREMENT_EXPRESSION