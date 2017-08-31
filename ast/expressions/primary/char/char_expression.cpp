#include "char_expression.h"

string char_expression::to_string()
{
    return "'" + string(&value) + "'" + " ";
}