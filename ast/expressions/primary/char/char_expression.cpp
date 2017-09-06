#include "char_expression.h"

string char_expression::to_string()
{
    return "'" + string(&value) + "'" + " ";
}

int char_expression::get_kind()
{
    return CHAR_EXPR;
}

string char_expression::get_type()
{
    return "char";
}