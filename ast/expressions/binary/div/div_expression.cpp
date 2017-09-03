#include "div_expression.h"

string div_expression::to_string()
{
    return expr1->to_string() + "/ " + expr2->to_string();
}

int div_expression::get_kind()
{
    return DIV_EXPR;
}