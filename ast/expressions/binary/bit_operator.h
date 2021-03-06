#ifndef BIT_OPERATOR
#define BIT_OPERATOR

#include "binary_expression.h"

class bit_operator : public binary_expression
{
public:
    bit_operator(expression *expr1, expression *expr2, int position, string op) : binary_expression(expr1, expr2, position, op)
    {
        rules["int,int"]    =   { INT, false, SIMPLE, false };
        rules["int,char"]   =   { INT, false, SIMPLE, false };
        rules["char,int"]   =   { INT, false, SIMPLE, false };
        rules["char,char"]  =   { INT, false, SIMPLE, false };
        lvalue = false;
    }
};

#endif // BIT_OPERATOR