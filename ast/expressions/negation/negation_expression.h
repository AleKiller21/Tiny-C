#ifndef NEGATION_EXPRESSION
#define NEGATION_EXPRESSION

#include "../unary_expression.h"

class negation_expression : public unary_expression
{
public:
    negation_expression(expression* expr) : unary_expression(expr) {}
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // NEGATION_EXPRESSION