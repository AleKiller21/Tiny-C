#include "address_expression.h"

string address_expression::to_string()
{
    return "&" + expr->to_string();
}