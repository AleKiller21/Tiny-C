#include "string_expression.h"

string string_expression::to_string()
{
    return + "\"" + value + "\"" + " ";
}

int string_expression::get_kind()
{
    return STRING_EXPR;
}

string string_expression::get_type()
{
    return "string";
}