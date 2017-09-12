#include "array_declarator.h"

string array_declarator::to_string()
{
    if(has_range())
        return get_id() + "[" + index_expr->to_string() + "]" + declarator::to_string();

        return get_id() + "[" + "]" + declarator::to_string();
}

bool array_declarator::has_range()
{
    return index_expr != NULL;
}

void array_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(!validate_type(id) || !validate_pointer(id) || !validate_range(id)) return;
    if(!validate_existance(id, sym, get_kind())) return;
    if(!validate_initialization()) return;
    
    if(sym == NULL)
    {
        bool is_initialized = init != NULL ? true : false;
        sym_table.add_symbol(id, new symbol { type, get_position(), is_initialized , pointer, get_kind(), this } );
        if(!is_initialized) redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else if(init != NULL)
    {
        sym_table.replace_symbol(id, new symbol { type, get_position(), true, pointer, get_kind(), this });
        redund_manager.make_all_removable(id);
    }

    else if((has_range() && !((array_declarator*)sym->decl_ptr)->has_range()) && !sym->is_initialized)
    {
        sym_table.replace_symbol(id, new symbol { type, get_position(), false, pointer, get_kind(), this });
        redund_manager.make_all_removable(id);
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
    //TODO: Validar que para todos los declaradores globales, si estos no tienen valor asignado o rango(arreglos) entonces asignarle default value, 0
}

bool array_declarator::validate_initialization()
{
    if(init == NULL) return true;

    if(init->list_expr == NULL)
    {
        comp_utils::show_message("error", "invalid initializer", get_position());
        return false;
    }

    //TODO: Obtener el tipo de las expresiones en el inicializador y en el rango
    return true;
}

bool array_declarator::validate_type(string id)
{
    if(type == VOID)
    {
        comp_utils::show_message("error", "declaration of '" + id + "' as array of voids", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_pointer(string id)
{
    if(pointer)
    {
        comp_utils::show_message("error", "declaration of array of pointers is not allowed in TinyC", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_range(string id)
{
    if(!validate_block_scope_range(id) || !validate_range_type(id)) return false;   
    return true;
}

bool array_declarator::validate_block_scope_range(string id)
{
    if(sym_table.get_scope_level() > 0 && !has_range() && init == NULL)
    {
        comp_utils::show_message("error", "array size missing in '" + id + "'", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_range_type(string id)
{
    if(has_range() && index_expr->get_kind() == STRING_EXPR)
    {
        comp_utils::show_message("error", "size of '" + id + "' has non-integer type", get_position());
        return false;
    }

    return true;
}