#include "assignment_expression.h"

string assignment_expression::to_string()
{
    return expr1->to_string() + "= " + expr2->to_string();
}

int assignment_expression::get_kind()
{
    return ASSIGN_EXPR;
}