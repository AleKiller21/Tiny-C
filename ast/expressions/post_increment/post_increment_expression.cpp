#include "post_increment_expression.h"

post_increment_expression::post_increment_expression(expression* expr)
{
    this->expr = expr;
}

string post_increment_expression::to_string()
{
    return expr->to_string() + "++ ";
}