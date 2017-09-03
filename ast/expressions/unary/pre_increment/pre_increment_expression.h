#ifndef PRE_INCREMENT_EXPRESSION
#define PRE_INCREMENT_EXPRESSION

#include "../unary_expression.h"

class pre_increment_expression : public unary_expression
{
public:
    pre_increment_expression(expression* expr, int position) : unary_expression(expr, position) {}
    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // PRE_INCREMENT_EXPRESSION