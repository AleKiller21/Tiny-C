#include "address_expression.h"

string address_expression::to_string()
{
    return "&" + expr->to_string();
}

int address_expression::get_kind()
{
    return ADDRESS_EXPR;
}