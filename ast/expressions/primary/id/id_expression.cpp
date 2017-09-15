#include "id_expression.h"

string id_expression::to_string()
{
   return lexeme + " ";
}

string id_expression::get_lexeme()
{
    return lexeme;
}

id_attributes id_expression::get_type()
{
    symbol *sym = sym_table.get_symbol(lexeme);
    if(sym == NULL)
    {
        comp_utils::show_message("error", "'" + lexeme + "' undeclared (first use in this function)", position);
        return { 0, 0, 0, true };
    }

    is_global = sym->is_global;
    return { sym->type, sym->pointer, sym->category, false };
}

int id_expression::get_kind()
{
    return ID_EXPR;
}

asm_code* id_expression::generate_code(stack_manager *manager)
{
    string reg = reg_manager.get_free_register(false);
    string code;

    if(is_global) code = choose_load_format(data_section[lexeme]) + reg + ", " + lexeme + "\n";
    else code = manager->load_from_var(reg, lexeme);

    return new asm_code { code, reg, -1 };
}

string id_expression::choose_load_format(string type)
{
    if(type == WORD) return "lw ";
    return "lb ";
}