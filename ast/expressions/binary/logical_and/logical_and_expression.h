#ifndef LOGICAL_AND_EXPRESSION
#define LOGICAL_AND_EXPRESSION

#include "../binary_expression.h"

class logical_and_expression : public binary_expression
{
public:
    logical_and_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position, "&&")
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // LOGICAL_AND_EXPRESSION