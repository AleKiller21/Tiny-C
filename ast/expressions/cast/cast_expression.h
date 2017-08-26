#ifndef CAST_EXPRESSION
#define CAST_EXPRESSION

#include "../expression.h"

class cast_expression : public expression
{
private:
    expression* expr;
    string type;
};

#endif // CAST_EXPRESSION