#ifndef POINTER_EXPRESSION
#define POINTER_EXPRESSION

#include "../unary_expression.h"

class pointer_expression : public unary_expression
{
public:
    pointer_expression(expression* expr, int position) : unary_expression(expr, position) { lvalue = true; }
    string to_string();
    int get_kind();
    id_attributes get_type();
    string *get_operand_id();
    // string generate_mips(); TODO: generar codigo para expresiones con apuntadores
};

#endif // POINTER_EXPRESSION