#include "int_expression.h"

int_expression::int_expression(int value, int format)
{
    this->value = value;
    this->format = format;
}

char int_expression::get_format()
{
    return format;
}