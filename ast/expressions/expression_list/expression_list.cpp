#include "expression_list.h"

void expression_list::add_expression(expression* expr)
{
    expressions.push_back(expr);
}

string expression_list::to_string()
{
    string source;

    for(list<expression*>::iterator it = expressions.begin(); it != expressions.end(); it++)
    {
        source += (*it)->to_string() + ", ";
    }

    return source;
}

int expression_list::get_kind()
{
    return LIST_EXPR;
}

list<expression*> expression_list::get_list()
{
    return expressions;
}

type_attributes expression_list::get_type()
{
    for(list<expression*>::iterator it = expressions.begin(); it != expressions.end(); it++)
    {
        type_attributes expr_type = (*it)->get_type();
        if(expr_type.semantic_fail) return expr_type;
        if(expr_type.type == VOID)
        {
            comp_utils::show_message("error", "void type is not allowed in a list of expressions", position);
            return { 0, 0, 0, true };
        }
    }

    return { INT, false, SIMPLE, false }; //Dummy value
}

asm_code *expression_list::generate_code(stack_manager *manager)
{
    printf("expression_list null generate_code()\n");
    return NULL;
}