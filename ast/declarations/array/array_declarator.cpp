#include "array_declarator.h"

string array_declarator::to_string()
{
    if(index_expr != NULL)
        return get_id() + "[" + index_expr->to_string() + "]" + declarator::to_string();

        return get_id() + "[" + "]" + declarator::to_string();
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

    if(sym_table.get_scope_level() > 0 && index_expr == NULL)
    {
        show_message("error", "array size missing in '" + id + "'");
        return;
    }

    if(!validate_existance(id, sym, ARRAY)) return;
    if(!validate_initialization()) return;
    

    sym_table.add_symbol(id, new symbol {type, get_position(), init != NULL ? true : false, pointer, ARRAY} );
}

bool array_declarator::validate_initialization()
{
    if(init == NULL) return true;

    if(init->list_expr == NULL)
    {
        show_message("error", "invalid initializer");
        return false;
    }
}