#include "greater_expression.h"

string greater_expression::to_string()
{
    return expr1->to_string() + "> " + expr2->to_string();
}