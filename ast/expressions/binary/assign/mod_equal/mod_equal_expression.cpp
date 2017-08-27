#include "mod_equal_expression.h"

string mod_equal_expression::to_string()
{
    return expr1->to_string() + "%= " + expr2->to_string();
}