#include "logical_and_expression.h"

string logical_and_expression::to_string()
{
    return expr1->to_string() + "&& " + expr2->to_string();
}