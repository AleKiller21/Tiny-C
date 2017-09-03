#include "post_increment_expression.h"

string post_increment_expression::to_string()
{
    return expr->to_string() + "++ ";
}

int post_increment_expression::get_kind()
{
    return POST_INC_EXPR;
}