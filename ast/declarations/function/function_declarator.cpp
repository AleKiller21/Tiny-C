#include "function_declarator.h"

string function_declarator::to_string()
{
    if(params != NULL) return get_id() + "(" + params->to_string() + ")" + declarator::to_string();

    return get_id() + "(" + ")" + declarator::to_string();
}

void function_declarator::validate_semantic()
{
    
}