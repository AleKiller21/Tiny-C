#include "function_declarator.h"

string function_declarator::to_string()
{
    if(params != NULL) return id_expr->to_string() + "(" + params->to_string() + ")" + declarator::to_string();

    return id_expr->to_string() + "(" + ")" + declarator::to_string();
}

void function_declarator::validate_semantic()
{
    
}