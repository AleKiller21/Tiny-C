#include "function_declarator.h"

string function_declarator::to_string()
{
    if(params != NULL) return decl->to_string() + "(" + params->to_string() + ")";

    return decl->to_string() + "(" + ")";
}