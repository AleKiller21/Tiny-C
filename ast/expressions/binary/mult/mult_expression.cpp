#include "mult_expression.h"

string mult_expression::to_string()
{
    return expr1->to_string() + "* " + expr2->to_string();
}