#ifndef ASSIGNMENT_EXPRESSION
#define ASSIGNMENT_EXPRESSION

#include "../binary_expression.h"

class assignment_expression : public binary_expression
{
public:
    assignment_expression(expression* expr1, expression* expr2, int position) : binary_expression(expr1, expr2, position, "=")
    {
        rules["int,int"]        = { INT, false, SIMPLE, false };
        rules["int,char"]       = { INT, false, SIMPLE, false };
        rules["char,int"]       = { CHAR, false, SIMPLE, false };
        rules["char,char"]      = { CHAR, false, SIMPLE, false };

        rules["int*,int*"]      = { INT, true, SIMPLE, false };
        rules["char*,char*"]    = { CHAR, true, SIMPLE, false };
    }
    string to_string();
    int get_kind();
    id_attributes get_type();
    //string generate_mips();
};

#endif // ASSIGNMENT_EXPRESSION