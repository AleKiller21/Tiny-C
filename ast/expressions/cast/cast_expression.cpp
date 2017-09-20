#include "cast_expression.h"

string cast_expression::to_string()
{
    return "(" + type->to_string() + ")" + expr->to_string();
}

int cast_expression::get_kind()
{
    return CAST_EXPR;
}

type_attributes cast_expression::get_type()
{
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    if(type->pointer && expr_type.kind == ARRAY) return { type->type, false, expr_type.kind, false };
    return { type->type, type->pointer, expr_type.kind, false };
}