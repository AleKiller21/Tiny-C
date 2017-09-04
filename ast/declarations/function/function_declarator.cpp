#include "function_declarator.h"

string function_declarator::to_string()
{
    string ptr = pointer ? "*" : "";

    if(params != NULL) return ptr + get_id() + "(" + params->to_string() + ")" + declarator::to_string();

    return ptr + get_id() + "(" + ")" + declarator::to_string();
}

vector<string> function_declarator::get_param_types()
{
    if(params == NULL) return vector<string>();
    return params->get_types();
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

    if(!compare_existing_symbol(id, sym)) return;
}

bool function_declarator::compare_existing_symbol(string id, symbol* sym)
{
    if(sym->category != FUNCTION)
    {
        show_message("error", "'" + id + "' redeclared as different kind of symbol");
        return false;
    }

    if(sym->type != type || sym->pointer != pointer)
    {
        show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " + std::to_string(sym->lineno));
        return false;
    }

    vector<string> prev_decl_param_types = ((function_declarator*)sym->decl_ptr)->get_param_types();
    vector<string> curr_decl_param_types = get_param_types();

    if(!compare_param_types(prev_decl_param_types, curr_decl_param_types))
    {
        show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " + std::to_string(sym->lineno));
        return false;
    }

    return true;
}

bool function_declarator::compare_param_types(vector<string> prev_decl, vector<string> curr_decl)
{
    if(prev_decl.size() != curr_decl.size()) return false;

    for(int i = 0; i < prev_decl.size(); i++)
    {
        if(prev_decl[i].compare(curr_decl[i]) != 0) return false;
    }

    return true;
}