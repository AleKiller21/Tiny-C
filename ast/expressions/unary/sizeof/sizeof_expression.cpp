#include "sizeof_expression.h"

string sizeof_expression::to_string()
{
    if(type == NULL) return "sizeof(" + expr->to_string() + ")";

    return "sizeof(" + type->to_string() + ")";
}