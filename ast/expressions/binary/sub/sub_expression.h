#ifndef SUB_EXPRESSION
#define SUB_EXPRESSION

#include "../binary_expression.h"

class sub_expression : public binary_expression
{
public:
    sub_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position, "-")
    {
        rules["int,int"]        =   { INT, false, SIMPLE, false };
        rules["int,char"]       =   { INT, false, SIMPLE, false };
        rules["char,int"]       =   { INT, false, SIMPLE, false };
        rules["char,char"]      =   { INT, false, SIMPLE, false };

        rules["int*,int"]       =   { INT, true, SIMPLE, false };
        rules["int*,char"]      =   { INT, true, SIMPLE, false };

        rules["char*,int"]      =   { CHAR, true, SIMPLE, false };
        rules["char*,char"]     =   { CHAR, true, SIMPLE, false };

        rules["int*,int*"]      =   { INT, false, SIMPLE, false };
        rules["char*,char*"]    =   { INT, false, SIMPLE, false };
    }

    string to_string();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // SUB_EXPRESSION