#include "two_complement_expression.h"

string two_complement_expression::to_string()
{
    return "~" + expr->to_string();
}