#ifndef ADDRESS_EXPRESSION
#define ADDRESS_EXPRESSION

#include "../unary_expression.h"

class address_expression : public unary_expression
{
public:
    address_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = false; }
    string to_string();
    int get_kind();
    type_attributes get_type();
    string *get_operand_id();
    // string generate_mips(); TODO: generar codigo para expresiones con ambersand
};

#endif // ADDRESS_EXPRESSION