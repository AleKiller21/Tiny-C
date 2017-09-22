#include "array_expression.h"

string array_expression::to_string()
{
    return expr->to_string() + "[" + index->to_string() + "]" + " ";
}

int array_expression::get_kind()
{
    return ARRAY_EXPR;
}

type_attributes array_expression::get_type()
{
    type_attributes index_type = index->get_type();
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    
    if((!expr_type.pointer && expr_type.kind != ARRAY) || (!comp_utils::is_type_int(expr_type) && !comp_utils::is_type_char(expr_type)))
    {
        comp_utils::show_message("error", "subscripted value is neither array nor pointer", position);
        return { 0, 0, 0, true};
    }

    if(index_type.semantic_fail) return index_type;
    
    if(!comp_utils::is_type_int(index_type) && (!comp_utils::is_type_char(index_type) || index_type.pointer))
    {
        comp_utils::show_message("error", "array subscript is not an integer", position);
        return { 0, 0, 0, true};
    }
    
    return { expr_type.type, false, SIMPLE, false };
}

asm_code *array_expression::generate_code(stack_manager *manager)
{
    string treg = reg_manager.get_register(false);
    return generate_array_expression_code(manager, treg);
}

asm_code *array_expression::generate_array_expression_code(stack_manager *manager, string reg, string memory_access_operation)
{
    asm_code *expr_code;
    asm_code *indx_expr = index->generate_code(manager);
    id_expression *id_expr = (id_expression*)expr;
    string *id = id_expr->get_operand_id();
    string mem_access = !memory_access_operation.compare("load") ? "\tl" : "\ts";
    string code;

    if(!index->is_code)
    {
        //TODO: tomar en consideracion que puede ser una aritmetica de apuntadores y no solo el id de un arreglo
        if(id_expr->is_global)
        {
            int offset;
            string base_reg = reg_manager.get_register(false);
            code = "\tla " + base_reg + ", " + *id + "\n";
            if(data_section[*id] == WORD) { code += mem_access + "w "; offset = indx_expr->constant * 4; }
            else { code += mem_access + "b "; offset = indx_expr->constant; }

            reg_manager.free_register(base_reg);
            code += reg + ", " + std::to_string(offset) + "(" + base_reg + ")" + "\n";
        }
        else
        {
            if(!memory_access_operation.compare("load")) code = manager->load_from_var(reg, *id, indx_expr->constant);
            else code = manager->store_into_var(reg, *id, indx_expr->constant);
        }
    }

    else
    {
        code = indx_expr->code;
        string base_reg = reg_manager.get_register(false);

        if(id_expr->is_global)
        {
            bool is_word = data_section[*id] == WORD;

            code += "\tla " + base_reg + ", " + *id + "\n";
            if(is_word) code += "\tsll " + indx_expr->place + ", " + indx_expr->place + ", 2\n";
            code += "\tadd " + base_reg + ", " + base_reg + ", " + indx_expr->place + "\n";
            if(is_word) code += mem_access + "w ";
            else code += mem_access + "b ";

            code += reg + ", " + "(" + base_reg + ")" + "\n";
        }
        else
        {
            int base_address_offset = manager->get_var_offset(*id);
            string type = manager->get_var_type(*id);

            code += "\taddi " + base_reg + ", $fp, " + std::to_string(base_address_offset) + "\n";
            if(type == WORD) code += "\tsll " + indx_expr->place + ", " + indx_expr->place + ", 2\n";
            code += "\tadd " + base_reg + ", " + base_reg + ", " + indx_expr->place + "\n";

            if(type == WORD) code += mem_access + "w ";
            else code += mem_access + "b ";

            code += reg + ", " + "(" + base_reg + ")" + "\n";
        }

        reg_manager.free_register(indx_expr->place);
        reg_manager.free_register(base_reg);
    }

    expr_code = new asm_code { code, reg, -1 };
    delete indx_expr;
    delete id_expr;
    delete id;

    return expr_code;
}
