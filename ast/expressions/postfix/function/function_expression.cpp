#include "function_expression.h"

string function_expression::to_string()
{
    if(arguments != NULL) return id->to_string() + "(" + arguments->to_string() + ")" + " ";
    return id->to_string() + "(" + ")" + " ";
}