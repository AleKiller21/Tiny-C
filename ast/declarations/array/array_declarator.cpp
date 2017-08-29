#include "array_declarator.h"

string array_declarator::to_string()
{
    if(index_expr != NULL)
        return id_expr->to_string() + "[" + index_expr->to_string() + "]" + declarator::to_string();

        return id_expr->to_string() + "[" + "]" + declarator::to_string();
}