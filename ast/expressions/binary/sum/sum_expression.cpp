#include "sum_expression.h"

string sum_expression::to_string()
{
    return expr1->to_string() + "+ " + expr2->to_string();
}