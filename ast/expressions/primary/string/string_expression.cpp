#include "string_expression.h"

string string_expression::to_string()
{
    return + "\"" + value + "\"" + " ";
}

string string_expression::get_lexeme()
{
    return value;
}

int string_expression::get_kind()
{
    return STRING_EXPR;
}

type_attributes string_expression::get_type()
{
    return { CHAR, true, SIMPLE, false };
}