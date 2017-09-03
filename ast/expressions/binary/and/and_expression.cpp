#include "and_expression.h"

string and_expression::to_string()
{
    return expr1->to_string() + "& " + expr2->to_string();
}

int and_expression::get_kind()
{
    return AND_EXPR;
}