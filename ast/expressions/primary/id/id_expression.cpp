#include "id_expression.h"

string id_expression::to_string()
{
   return lexeme + " ";
}

string *id_expression::get_operand_id()
{
    return new string(lexeme);
}

type_attributes id_expression::get_type()
{
    symbol *sym = sym_table.get_symbol(lexeme);
    if(sym == NULL)
    {
        comp_utils::show_message("error", "'" + lexeme + "' undeclared (first use in this function)", position);
        return { 0, 0, 0, true };
    }

    is_global = sym->is_global;
    kind = sym->category;
    return { sym->type, sym->pointer, sym->category, false };
}

int id_expression::get_kind()
{
    return ID_EXPR;
}

asm_code* id_expression::generate_code(stack_manager *manager)
{
    string treg = reg_manager.get_register(false);
    string code;

    if(kind == SIMPLE)
    {
        if(is_global) code = choose_load_format(data_section[lexeme]) + treg + ", " + lexeme + "\n";
        else code = manager->load_from_var(treg, lexeme);
    }

    //TODO: Considerar que el arreglo puede venir de argumento. Entonces seria un SIMPLE con puntero y habria que mandar la direccion base de este
    else if(kind == ARRAY)
    {
        if(is_global) code = "\tla " + treg + ", " + lexeme + "\n";
        else
        {
            int offset = manager->get_var_offset(lexeme);
            code = "\taddi " + treg + ", $fp, " + std::to_string(offset) + "\n";
        }
    }

    return new asm_code { code, treg, -1 };
}

string id_expression::choose_load_format(string type)
{
    if(type == WORD) return "\tlw ";
    return "\tlb ";
}