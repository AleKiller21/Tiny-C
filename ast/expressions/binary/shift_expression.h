#ifndef SHIFT_EXPRESSION
#define SHIFT_EXPRESSION

#include "binary_expression.h"

class shift_expression : public binary_expression
{
protected:
    shift_expression(expression *expr1, expression *expr2, int position ,string op) : binary_expression(expr1, expr2, position, op)
    {
        rules["int,int"]    =   { INT, false, SIMPLE, false };
        rules["int,char"]   =   { INT, false, SIMPLE, false };
        rules["char,int"]   =   { INT, false, SIMPLE, false };
        rules["char,char"]  =   { INT, false, SIMPLE, false };
    }
};

#endif //SHIFT_EXPRESSION