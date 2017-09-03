#ifndef SIZEOF_EXPRESSION
#define SIZEOF_EXPRESSION

#include "../unary_expression.h"
#include "../../../declarations/abstract_declarator.h"

class sizeof_expression : public unary_expression
{
private:
    abstract_declarator* type;

public:
    sizeof_expression(expression* expr, abstract_declarator* type, int position) : unary_expression(expr, position)
    {
        this->type = type;
    }

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // SIZEOF_EXPRESSION