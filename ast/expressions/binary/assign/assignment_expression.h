#ifndef ASSIGNMENT_EXPRESSION
#define ASSIGNMENT_EXPRESSION

#include "../binary_expression.h"

class assignment_expression : public binary_expression
{
public:
    assignment_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position)
    {
        //TODO: inicializar las reglas
    }

    //string get_type();
};

#endif // ASSIGNMENT_EXPRESSION