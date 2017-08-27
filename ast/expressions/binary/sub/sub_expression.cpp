#include "sub_expression.h"

string sub_expression::to_string()
{
    return expr1->to_string() + "- " + expr2->to_string();
}