#include "int_expression.h"

int_expression::int_expression(int value, char format)
{
    this->value = value;
    this->format = format;
}

char int_expression::get_format()
{
    return format;
}

string int_expression::to_string()
{
    return std::to_string(value) + " ";
}