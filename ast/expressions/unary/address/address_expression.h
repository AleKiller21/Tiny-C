#ifndef ADDRESS_EXPRESSION
#define ADDRESS_EXPRESSION

#include "../unary_expression.h"

class address_expression : public unary_expression
{
public:
    address_expression(expression* expr, int position) : unary_expression(expr, position) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // ADDRESS_EXPRESSION