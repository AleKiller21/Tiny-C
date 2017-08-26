#ifndef BINARY_EXPRESSION
#define BINARY_EXPRESSION

#include <map>
#include "../expression.h"

class binary_expression : public expression
{
protected:
    expression *expr1, *expr2;
    map<string, string> rules;

    binary_expression(expression* expr1, expression* expr2, int position) : expression(position)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
    }
};

#endif // BINARY_EXPRESSION