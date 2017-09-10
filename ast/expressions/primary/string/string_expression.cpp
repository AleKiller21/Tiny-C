#include "string_expression.h"

string string_expression::to_string()
{
    return + "\"" + value + "\"" + " ";
}

int string_expression::get_kind()
{
    return STRING_EXPR;
}

id_attributes* string_expression::get_type()
{
    return new id_attributes { CHAR, true, SIMPLE };
}