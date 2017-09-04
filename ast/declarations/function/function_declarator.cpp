#include "function_declarator.h"

string function_declarator::to_string()
{
    string ptr = pointer ? "*" : "";

    if(params != NULL) return ptr + get_id() + "(" + params->to_string() + ")" + declarator::to_string();

    return ptr + get_id() + "(" + ")" + declarator::to_string();
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

    if(sym == NULL)
    {
        sym_table.add_symbol(id, new symbol { type, get_position(), false , pointer, get_kind(), this } );
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
        return;
    }

    if(sym->category != get_kind())
    {
        show_message("error", "'" + id + "' redeclared as different kind of symbol");
        return;
    }

    if(sym->type != type || sym->pointer != pointer)
    {
        show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " + std::to_string(sym->lineno));
        return;
    }
}