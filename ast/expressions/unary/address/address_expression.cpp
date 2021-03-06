#include "address_expression.h"

string address_expression::to_string()
{
    return "&" + expr->to_string();
}

int address_expression::get_kind()
{
    return ADDRESS_EXPR;
}

type_attributes address_expression::get_type()
{
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    if(!expr->get_lvalue() || expr_type.kind == FUNCTION)
    {
        comp_utils::show_message("error", "invalid type argument of unary '&'", position);
        return {0, 0, 0, true };
    }

    return { expr_type.type, true, SIMPLE, false };
}

string *address_expression::get_operand_id()
{
    return expr->get_operand_id();
}