#ifndef LOGICAL_OR_EXPRESSION
#define LOGICAL_OR_EXPRESSION

#include "../binary_expression.h"

class logical_or_expression : public binary_expression
{
public:
    logical_or_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position)
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // LOGICAL_OR_EXPRESSION