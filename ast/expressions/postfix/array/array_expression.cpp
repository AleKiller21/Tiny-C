#include "array_expression.h"

string array_expression::to_string()
{
    return expr->to_string() + "[" + index->to_string() + "]" + " ";
}

int array_expression::get_kind()
{
    return ARRAY_EXPR;
}

id_attributes* array_expression::get_type()
{
    id_attributes* index_type = index->get_type();
    id_attributes* expr_type = expr->get_type();
    id_attributes* type;

    if(expr_type == NULL) return NULL;
    
    if((!expr_type->pointer && expr_type->kind != ARRAY) || (!comp_utils::is_type_int(*expr_type) && !comp_utils::is_type_char(*expr_type)))
    {
        comp_utils::show_message("error", "subscripted value is neither array nor pointer", position);
        return NULL;
    }

    if(index_type == NULL) return NULL;
    if(!comp_utils::is_type_int(*index_type) && (!comp_utils::is_type_char(*index_type) || index_type->pointer))
    {
        comp_utils::show_message("error", "array subscript is not an integer", position);
        return NULL;
    }

    type = new id_attributes { expr_type->type, false, SIMPLE };
    delete index_type;
    delete expr_type;
    return type;
}