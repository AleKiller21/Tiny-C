#include "positive_expression.h"

string positive_expression::to_string()
{
    return "+" + expr->to_string();
}