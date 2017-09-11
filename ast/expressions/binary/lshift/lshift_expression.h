#ifndef LSHIFT_EXPRESSION
#define LSHIFT_EXPRESSION

#include "../binary_expression.h"

class lshift_expression : public binary_expression
{
public:
    lshift_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position, "<<")
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // LSHIFT_EXPRESSION