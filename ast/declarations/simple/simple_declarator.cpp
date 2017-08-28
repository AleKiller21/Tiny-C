#include "simple_declarator.h"

string simple_declarator::to_string()
{
    if(pointer) return "*" + id_expr->to_string();
    return id_expr->to_string();
}