#include "pointer_expression.h"

string pointer_expression::to_string()
{
    return "*" + expr->to_string();
}

int pointer_expression::get_kind()
{
    return POINTER_EXPR;
}