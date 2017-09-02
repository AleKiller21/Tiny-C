#include "simple_declarator.h"

string simple_declarator::to_string()
{
    if(pointer) return "*" + id_expr->to_string() + declarator::to_string();
    return id_expr->to_string() + declarator::to_string();
}

void simple_declarator::validate_semantic()
{
    if(type == VOID)
    {
        show_error("variable or field '" + get_id() + "' declared void");
        return;
    }
    
    if(!validate_existance()) return;
    //if(!validate_initialization()) return;
    sym_table.add_symbol(get_id(), new symbol {type, get_position(), true} );
}

bool simple_declarator::validate_existance()
{
    string id = get_id();
    symbol* symbol = sym_table.exist_symbol_in_current_scope(id);
    if(symbol == NULL) return true;

    if(symbol->is_initialized && init != NULL)
    {
        show_error("Redefinition of '" + id + "'\nprevious definition was found at line " + std::to_string(symbol->lineno));
        return false;
    }

    if(sym_table.get_scope_level() > 0)
    {
        show_error("Redeclaration of '" + id + "'\nprevious declaration was found at line " + std::to_string(symbol->lineno));
        return false;
    }

    if(sym_table.get_scope_level() == 0 && init == NULL) return true;
    return true;
}

bool simple_declarator::validate_initialization()
{

}