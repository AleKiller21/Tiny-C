#include "simple_declarator.h"

string simple_declarator::to_string()
{
    if(pointer) return "*" + id_expr->to_string() + declarator::to_string();
    return id_expr->to_string() + declarator::to_string();
}

void simple_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(type == VOID)
    {
        show_error("variable or field '" + id + "' declared void");
        return;
    }
    
    if(!validate_existance(id, sym)) return;
    if(!validate_initialization()) return;

    if(sym == NULL) sym_table.add_symbol(id, new symbol {type, get_position(), init != NULL ? true : false } );
    else if(init != NULL) sym->is_initialized = true;
}

bool simple_declarator::validate_initialization()
{
    if(init == NULL) return true;
    //TODO: Mandar a llamar el get_type de init y compararlo con el tipo del declarador
    return true;    
}