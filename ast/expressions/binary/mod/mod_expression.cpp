#include "mod_expression.h"

string mod_expression::to_string()
{
    return expr1->to_string() + "% " + expr2->to_string();
}