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

type_attributes sizeof_expression::get_type()
{
    if(type != NULL) return { INT, false, SIMPLE, false };

    type_attributes expr_type = expr->get_type();
    if(expr_type.semantic_fail) return expr_type;
    if(expr_type.kind != ARRAY) return { INT, false, SIMPLE, false };

    string *arr_id = expr->get_operand_id();
    symbol *arr_symbol = sym_table.get_symbol(*arr_id);

    delete arr_id;
    
    if(!arr_symbol->is_initialized && !((array_declarator*)arr_symbol->decl_ptr)->has_range())
    {
        string result = comp_utils::type_to_string(expr_type.type);        
        comp_utils::show_message("error", "invalid application of ‘sizeof’ to incomplete type " + result + "[]", position);
        return { 0, 0, 0, true };
    }

    return { INT, false, SIMPLE, false };
}

asm_code *sizeof_expression::generate_code(stack_manager *manager)
{
    if(type != NULL)
    {
        if(type->pointer) return new asm_code { "", "", sizeof(int) };
        if(type->type == INT) return new asm_code { "", "", sizeof(int) };
        if(type->type == CHAR) return new asm_code { "", "", sizeof(char) };
    }

    if(expr->get_kind() != ID_EXPR) return new asm_code { "", "", sizeof(int) };

    string *operand_id = expr->get_operand_id();
    asm_code *expr_code;
    string type;

    if(((id_expression*)expr)->is_global) type = data_section[*operand_id];
    else type = manager->vars[*operand_id].asm_type;

    if(type == WORD) expr_code = new asm_code { "", "", sizeof(int) };
    else expr_code = new asm_code { "", "", sizeof(char) };

    delete operand_id;
    return expr_code;
}