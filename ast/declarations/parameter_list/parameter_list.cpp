#include "parameter_list.h"

string parameter_list::to_string()
{
    string str;
    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        switch((*it)->type)
        {
            case INT:
                str += "int ";
                break;
            case CHAR:
                str += "char ";
                break;
            case VOID:
                str += "void ";
                break;
        }
        
        str += (*it)->to_string() + ", ";
    }

    return str;
}

vector<type_attributes> parameter_list::get_types()
{
    vector<type_attributes> types;

    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
        types.push_back({ (*it)->type, (*it)->pointer, (*it)->get_kind() });

    return types;
}

void parameter_list::add_param(declarator* param)
{
    params.push_back(param);
}

bool parameter_list::validate_semantic(bool calculate_stack_displacement)
{
    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        declarator* decl = *it;
        string id = decl->get_id();
        symbol* sym =  sym_table.exist_symbol_in_current_scope(id);

        if(sym != NULL)
        {
            comp_utils::show_message("error", "redefinition of parameter '" + id + "'\n previous definition was found at line " +
                std::to_string(sym->lineno), decl->get_position());
            continue;
        }

        if(decl->type == VOID)
        {
            comp_utils::show_message("error", "parameter '" + id + "' declared void", decl->get_position());
            continue;
        }

        if(decl->get_kind() == FUNCTION)
        {
            comp_utils::show_message("error", "Passing function pointers is not allowed in TinyC", decl->get_position());
            continue;
        }

        if(decl->get_kind() == ARRAY)
        {
            compiler::increase_stack_displacement(4);
            array_declarator* arr_decl = (array_declarator*)decl;
            if(!arr_decl->validate_pointer(id) || !arr_decl->validate_range_type(id)) continue;
            sym_table.add_symbol(id, new symbol { decl->type, decl->get_position(), true , true, SIMPLE, decl } );
            continue;
        }

        if ((decl->type == INT || decl->pointer) && calculate_stack_displacement) compiler::increase_stack_displacement(4);
        else if(calculate_stack_displacement) compiler::increase_stack_displacement(1);
        
        sym_table.add_symbol(id, new symbol { decl->type, decl->get_position(), true , decl->pointer, SIMPLE, decl } );
    }

    return true;
}

int parameter_list::get_params_amount()
{
    return params.size();
}

list<declarator*> parameter_list::get_params()
{
    return params;
}