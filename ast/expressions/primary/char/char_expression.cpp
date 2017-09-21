#include "char_expression.h"

string char_expression::to_string()
{
    return "'" + string(&value) + "'" + " ";
}

int char_expression::get_kind()
{
    return CHAR_EXPR;
}

int char_expression::get_value()
{
    return value;
}

type_attributes char_expression::get_type()
{
    return { CHAR, false, SIMPLE, false };
}

asm_code *char_expression::generate_code(stack_manager *manager)
{
    return new asm_code { "", "", value };
}