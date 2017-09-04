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

    if(type == VOID)
    {
        show_message("error", "declaration of '" + id + "' as array of voids");
        return;
    }

    if(pointer)
    {
        show_message("error", "declaration of array of pointers is not allowed in TinyC");
        return;
    }

    if(sym_table.get_scope_level() > 0 && !has_range())
    {
        show_message("error", "array size missing in '" + id + "'");
        return;
    }

    if(has_range() && index_expr->get_kind() == STRING_EXPR)
    {
        show_message("error", "size of '" + id + "' has non-integer type");
        return;
    }

    if(!validate_existance(id, sym, ARRAY)) return;
    if(!validate_initialization()) return;
    
    if(sym == NULL)
    {
        bool is_initialized = init != NULL ? true : false;
        sym_table.add_symbol(id, new symbol { type, get_position(), is_initialized , pointer, ARRAY, this } );
        if(!is_initialized) redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else if(init != NULL)
    {
        sym_table.remove_symbol(id);
        sym_table.add_symbol(id, new symbol { type, get_position(), true, pointer, ARRAY, this });
        redund_manager.make_all_removable(id);
    }

    else if((has_range() && !((array_declarator*)sym->decl_ptr)->has_range()) && !sym->is_initialized)
    {
        sym_table.remove_symbol(id);
        sym_table.add_symbol(id, new symbol { type, get_position(), false, pointer, ARRAY, this });
        redund_manager.make_all_removable(id);
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
}

bool array_declarator::validate_initialization()
{
    if(init == NULL) return true;

    if(init->list_expr == NULL)
    {
        show_message("error", "invalid initializer");
        return false;
    }

    //TODO: Obtener el tipo de las expresiones en el inicializador y en el rango
    return true;
}