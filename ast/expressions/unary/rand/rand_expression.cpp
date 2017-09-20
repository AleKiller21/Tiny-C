#include "rand_expression.h"

string rand_expression::to_string()
{
    return "rand() ";
}

int rand_expression::get_kind()
{
    return SRAND_EXPR;
}

type_attributes rand_expression::get_type()
{
    return { INT, false, SIMPLE, false };
}

asm_code *rand_expression::generate_code(stack_manager *manager)
{
    return new asm_code { "\tjal rand\n", "$v0", -1 };
}