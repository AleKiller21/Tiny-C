#include "equal_expression.h"

string equal_expression::to_string()
{
    return expr1->to_string() + "== " + expr2->to_string();
}