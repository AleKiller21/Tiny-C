#include "not_equal_expression.h"

string not_equal_expression::to_string()
{
    return expr1->to_string() + "!= " + expr2->to_string();
}

int not_equal_expression::get_kind()
{
    return NE_EXPR;
}