#ifndef MULTIPLICATIVE_EXPRESSION
#define MULTIPLICATIVE_EXPRESSION

#include "binary_expression.h"

class multiplicative_expression : public binary_expression
{
protected:
    multiplicative_expression(expression *expr1, expression *expr2, int position, string op) : binary_expression(expr1, expr2, position, op)
    {
        rules["int,int"]    = { INT, false, SIMPLE, false };
        rules["int,char"]   = { INT, false, SIMPLE, false };
        rules["char,int"]   = { INT, false, SIMPLE, false };
        rules["char,char"]  = { INT, false, SIMPLE, false };
    }    
};

#endif // MULTIPLICATIVE_EXPRESSION