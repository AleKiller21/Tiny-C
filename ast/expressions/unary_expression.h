#ifndef UNARY_EXPRESSION
#define UNARY_EXPRESSION

#include "expression.h"

class unary_expression : public expression
{
protected:
    expression* expr;
    
    unary_expression(expression* expr, int position) : expression(position) { this->expr = expr; }
};

#endif // UNARY_EXPRESSION