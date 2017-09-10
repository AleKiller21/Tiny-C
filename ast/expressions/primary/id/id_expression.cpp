#include "id_expression.h"

string id_expression::to_string()
{
   return lexeme + " ";
}

string id_expression::get_lexeme()
{
    return lexeme;
}

id_attributes* id_expression::get_type()
{
    symbol *sym = sym_table.get_symbol(lexeme);
    if(sym == NULL)
    {
        comp_utils::show_message("error", "'" + lexeme + "' undeclared (first use in this function)", position);
        return NULL;
    }

    if(sym->category != ARRAY) lvalue = true;
    else lvalue = false;

    return new id_attributes { sym->type, sym->pointer, sym->category };
}

int id_expression::get_kind()
{
    return ID_EXPR;
}