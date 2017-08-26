#ifndef MOD_EXPRESSION
#define MOD_EXPRESSION

#include "../binary_expression.h"

class mod_expression : public binary_expression
{
public:
    mod_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position)
    {
        //TODO: inicializar las reglas
    }

    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // MOD_EXPRESSION