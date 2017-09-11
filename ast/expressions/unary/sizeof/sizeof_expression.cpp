#include "sizeof_expression.h"

string sizeof_expression::to_string()
{
    if(type == NULL) return "sizeof(" + expr->to_string() + ")";

    return "sizeof(" + type->to_string() + ")";
}

int sizeof_expression::get_kind()
{
    return SIZEOF_EXPR;
}

id_attributes sizeof_expression::get_type()
{
    if(type != NULL) return { INT, false, SIMPLE, false };

    id_attributes expr_type = expr->get_type();
    if(expr_type.semantic_fail) return expr_type;
    if(expr_type.kind != ARRAY) return { INT, false, SIMPLE, false };

    symbol *arr_symbol = sym_table.get_symbol(((id_expression*)expr)->get_lexeme());
    if(!arr_symbol->is_initialized && !((array_declarator*)arr_symbol->decl_ptr)->has_range())
    {
        string result = comp_utils::type_to_string(expr_type.type);        
        comp_utils::show_message("error", "invalid application of ‘sizeof’ to incomplete type " + result + "[]", position);
        return { 0, 0, 0, true };
    }

    return { INT, false, SIMPLE, false };
}