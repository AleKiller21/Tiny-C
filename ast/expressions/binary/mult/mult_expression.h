#ifndef MULT_EXPRESSION
#define MULT_EXPRESSION

#include "../binary_expression.h"

class mult_expression : public binary_expression
{
public:
    mult_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position)
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // MULT_EXPRESSION