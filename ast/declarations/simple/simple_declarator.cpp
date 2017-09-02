#include "simple_declarator.h"

string simple_declarator::to_string()
{
    if(pointer) return "*" + get_id() + declarator::to_string();
    return get_id() + declarator::to_string();
}

void simple_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(type == VOID)
    {
        show_message("error", "variable or field '" + id + "' declared void");
        return;
    }
    
    if(!validate_existance(id, sym, SIMPLE)) return;
    if(!validate_initialization()) return;

    if(sym == NULL) sym_table.add_symbol(id, new symbol {type, get_position(), init != NULL ? true : false, pointer, SIMPLE} );
    else if(init != NULL) sym->is_initialized = true;
}

bool simple_declarator::validate_initialization()
{
    if(init == NULL) return true;
    if(init->list_expr != NULL)
    {
        list<expression*> expressions = init->list_expr->get_list();
        if(expressions.size() > 1)
        {
            show_message("warning", "excess elements in scalar initializer");
            init->single_expr = expressions.front();
            for(list<expression*>::iterator it = ++expressions.begin(); it != expressions.end(); it++) delete *it;
            delete init->list_expr;
            init->list_expr = NULL;
        }

        else
        {
            init->single_expr = expressions.front();
            delete init->list_expr;
            init->list_expr = NULL;
        }
    }

    //TODO: Mandar a llamar el get_type de init->single_expr y compararlo con el tipo del declarador
    return true;    
}