#include "string_expression.h"

string_expression::string_expression(string value)
{
    this->value = value;
}

string string_expression::to_string()
{
    return value + " ";
}