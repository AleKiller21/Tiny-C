#include "pre_increment_expression.h"

string pre_increment_expression::to_string()
{
    return "++" + expr->to_string();
}

int pre_increment_expression::get_kind()
{
    return PRE_INC_EXPR;
}