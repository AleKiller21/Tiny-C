#include "xor_equal_expression.h"

string xor_equal_expression::to_string()
{
    return expr1->to_string() + "^= " + expr2->to_string();
}