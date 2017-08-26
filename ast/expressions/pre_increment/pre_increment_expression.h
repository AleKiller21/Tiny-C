#ifndef PRE_INCREMENT_EXPRESSION
#define PRE_INCREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_increment_expression : public unary_expression
{
public:
    pre_increment_expression(expression* expr) : unary_expression(expr) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // PRE_INCREMENT_EXPRESSION