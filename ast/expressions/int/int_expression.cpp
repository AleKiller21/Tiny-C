#include "int_expression.h"

char int_expression::get_format()
{
    return format;
}

string int_expression::to_string()
{
    return std::to_string(value) + " ";
}