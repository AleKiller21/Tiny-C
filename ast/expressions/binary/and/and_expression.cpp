#include "and_expression.h"

string and_expression::to_string()
{
    return expr1->to_string() + "& " + expr2->to_string();
}