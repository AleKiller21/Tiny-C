#ifndef SUM_EXPRESSION
#define SUM_EXPRESSION

#include "../binary_expression.h"

class sum_expression : public binary_expression
{
public:
    sum_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position)
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // SUM_EXPRESSION