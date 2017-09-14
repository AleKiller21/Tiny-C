#include "function_declarator.h"

string function_declarator::to_string()
{
    string ptr = pointer ? "*" : "";

    if(params != NULL) return ptr + get_id() + "(" + params->to_string() + ")" + declarator::to_string();

    return ptr + get_id() + "(" + ")" + declarator::to_string();
}

vector<id_attributes> function_declarator::get_param_types()
{
    if(params == NULL) return vector<id_attributes>();
    return params->get_types();
}

void function_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(init != NULL)
    {
        comp_utils::show_message("error", "function '" + id + "' is initialized like a variable", get_position());
        return;
    }

    if(sym == NULL)
    {
        sym_table.push_scope();
        validate_params();
        sym_table.pop_scope();

        sym_table.add_symbol(id, new symbol { type, get_position(), false , pointer, get_kind(), this } );
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
        return;
    }

    if(!compare_existing_symbol(id, sym)) return;

    sym_table.push_scope();
    validate_params();
    sym_table.pop_scope();

    redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
}

bool function_declarator::compare_existing_symbol(string id, symbol* sym)
{
    if(sym->category != FUNCTION)
    {
        comp_utils::show_message("error", "'" + id + "' redeclared as different kind of symbol", get_position());
        return false;
    }

    if(sym->type != type || sym->pointer != pointer)
    {
        comp_utils::show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " +
            std::to_string(sym->lineno), get_position());
        return false;
    }

    vector<id_attributes> prev_decl_param_types = ((function_declarator*)sym->decl_ptr)->get_param_types();
    vector<id_attributes> curr_decl_param_types = get_param_types();

    if(!compare_param_types(prev_decl_param_types, curr_decl_param_types))
    {
        comp_utils::show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " +
            std::to_string(sym->lineno), get_position());
        return false;
    }

    return true;
}

bool function_declarator::compare_param_types(vector<id_attributes> prev_decl, vector<id_attributes> curr_decl)
{
    if(prev_decl.size() != curr_decl.size()) return false;

    for(int i = 0; i < prev_decl.size(); i++)
    {
        if(prev_decl[i].type != curr_decl[i].type) return false;
        if(prev_decl[i].kind != curr_decl[i].kind)
        {
            if(prev_decl[i].kind == ARRAY && curr_decl[i].pointer) continue;
            if(curr_decl[i].kind == ARRAY && prev_decl[i].pointer) continue;
            return false;
        }

        if(prev_decl[i].pointer != curr_decl[i].pointer) return false;
    }

    return true;
}

bool function_declarator::validate_params()
{
    if(params == NULL) return true;
    if(params->get_params_amount() > 4)
    {
        comp_utils::show_message("error", "TinyC does not allows functions with more than four parameters", get_position());
        return false;
    }
    
    return params->validate_semantic();
}

string* function_declarator::generate_code()
{
    if(redund_declaration) return new string();
    return new string(get_id() + ":\n");
}