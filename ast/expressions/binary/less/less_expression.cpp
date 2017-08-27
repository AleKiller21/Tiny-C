#include "less_expression.h"

string less_expression::to_string()
{
    return expr1->to_string() + "< " + expr2->to_string();
}