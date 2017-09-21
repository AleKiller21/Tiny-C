#include "int_expression.h"

char int_expression::get_format()
{
    return format;
}

string int_expression::to_string()
{
    return std::to_string(value) + " ";
}

int int_expression::get_kind()
{
    return INT_EXPR;
}

int int_expression::get_value()
{
    return value;
}

type_attributes int_expression::get_type()
{
    return { INT, false, SIMPLE, false };
}

asm_code *int_expression::generate_code(stack_manager *manager)
{
    //TODO: evaluar el formato del int
    return new asm_code { "", "", value };
}