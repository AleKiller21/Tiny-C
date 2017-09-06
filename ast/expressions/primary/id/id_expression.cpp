#include "id_expression.h"

string id_expression::to_string()
{
   return lexeme + " ";
}

string id_expression::get_lexeme()
{
    return lexeme;
}

string id_expression::get_type()
{
    symbol *sym = sym_table.get_symbol(lexeme);
    if(sym == NULL)
    {
        comp_utils::show_message("error", "'" + lexeme + "' undeclared (first use in this function)", position);
        return "";
    }

    return comp_utils::get_type_lexeme(sym->type);
}

int id_expression::get_kind()
{
    return ID_EXPR;
}