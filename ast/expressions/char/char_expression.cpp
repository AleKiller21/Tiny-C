#include "char_expression.h"

char_expression::char_expression(char value)
{
    this->value = value;
}

string char_expression::to_string()
{
    return string(&value) + " ";
}