#include "int_expression.h"

char int_expression::get_format()
{
    return format;
}

string int_expression::to_string()
{
    return std::to_string(value) + " ";
}

int int_expression::get_kind()
{
    return INT_EXPR;
}

id_attributes* int_expression::get_type()
{
    return new id_attributes { INT, false, SIMPLE };
}