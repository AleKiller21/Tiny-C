#include "post_increment_expression.h"

string post_increment_expression::to_string()
{
    return expr->to_string() + "++ ";
}