#include "function_declarator.h"

string function_declarator::to_string()
{
    if(params != NULL) return get_id() + "(" + params->to_string() + ")" + declarator::to_string();

    return get_id() + "(" + ")" + declarator::to_string();
}

void function_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(init != NULL)
    {
        show_message("error", "function '" + id + "' is initialized like a variable");
        return;
    }

    
}