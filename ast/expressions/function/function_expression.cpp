#include "function_expression.h"

function_expression::function_expression(expression* id, expression* arguments)
{
    this->id = id;
    this->arguments = arguments;
}

string function_expression::to_string()
{
    return id->to_string() + "(" + arguments->to_string() + ")" + " ";
}