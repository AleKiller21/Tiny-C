#include "xor_expression.h"

string xor_expression::to_string()
{
    return expr1->to_string() + "^ " + expr2->to_string();
}

int xor_expression::get_kind()
{
    return XOR_EXPR;
}