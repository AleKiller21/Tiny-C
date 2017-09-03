#include "lshift_expression.h"

string lshift_expression::to_string()
{
    return expr1->to_string() + "<< " + expr2->to_string();
}

int lshift_expression::get_kind()
{
    return LSHIFT_EXPR;
}