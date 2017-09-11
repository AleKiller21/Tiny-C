#ifndef EQUAL_EXPRESSION
#define EQUAL_EXPRESSION

#include "../binary_expression.h"

class equal_expression : public binary_expression
{
public:
    equal_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position, "==")
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // EQUAL_EXPRESSION