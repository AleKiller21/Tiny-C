#include "char_expression.h"

string char_expression::to_string()
{
    return "'" + string(&value) + "'" + " ";
}

int char_expression::get_kind()
{
    return CHAR_EXPR;
}

id_attributes* char_expression::get_type()
{
    return new id_attributes { CHAR, false, SIMPLE };
}