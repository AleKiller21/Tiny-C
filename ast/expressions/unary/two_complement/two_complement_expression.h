#ifndef TWO_COMPLEMENT
#define TWO_COMPLEMENT

#include "../unary_expression.h"

class two_complement_expression : public unary_expression
{
public:
    two_complement_expression(expression* expr, int position) : unary_expression(expr, position) {}
    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // TWO_COMPLEMENT