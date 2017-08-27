#include "rshift_expression.h"

string rshift_expression::to_string()
{
    return expr1->to_string() + ">> " + expr2->to_string();
}