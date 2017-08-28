#include "array_declarator.h"

string array_declarator::to_string()
{
    if(index_expr != NULL)
        return decl->to_string() + "[" + index_expr->to_string() + "]";

        return decl->to_string() + "[" + "]";
}