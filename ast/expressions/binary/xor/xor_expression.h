#ifndef XOR_EXPRESSION
#define XOR_EXPRESSION

#include "../bit_operator.h"

class xor_expression : public bit_operator
{
public:
    xor_expression(expression* expr1, expression* expr2, int position) : bit_operator(expr1, expr2, position, "^") {}

    string to_string();
    int get_kind();
    // string generate_mips();
};

#endif // XOR_EXPRESSION