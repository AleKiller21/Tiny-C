#ifndef SUM_EXPRESSION
#define SUM_EXPRESSION

#include "../binary_expression.h"

class sum_expression : public binary_expression
{
public:
    sum_expression(expression *expr1, expression *expr2, int position) : binary_expression(expr1, expr2, position, "+")
    {
        rules["int,int"]    = { INT, false, SIMPLE, false };
        rules["int,char"]   = { INT, false, SIMPLE, false };
        rules["char,int"]   = { INT, false, SIMPLE, false };
        rules["char,char"]  = { INT, false, SIMPLE, false };

        rules["int*,int"]   = { INT, true, SIMPLE, false };
        rules["int,int*"]   = { INT, true, SIMPLE, false };
        rules["int*,char"]  = { INT, true, SIMPLE, false };
        rules["char,int*"]  = { INT, true, SIMPLE, false };

        rules["char*,int"]  = { CHAR, true, SIMPLE, false };
        rules["int,char*"]  = { CHAR, true, SIMPLE, false };
        rules["char*,char"] = { CHAR, true, SIMPLE, false };
        rules["char,char*"] = { CHAR, true, SIMPLE, false };
    }

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // SUM_EXPRESSION