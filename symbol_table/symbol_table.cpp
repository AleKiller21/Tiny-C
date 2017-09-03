#include "symbol_table.h"

symbol_table::symbol_table()
{
    scope_ptr = new scope;
    scope_ptr->outer_scope = NULL;
    scope_level = 0;
}

symbol* symbol_table::get_symbol(string id)
{
    scope* current_scope = scope_ptr;

    while(current_scope != NULL)
    {
        try { return current_scope->symbols.at(id); }
        catch(out_of_range) { current_scope = current_scope->outer_scope; }
    }

    return NULL;
}

int symbol_table::get_scope_level()
{
    return scope_level;
}

symbol* symbol_table::exist_symbol_in_current_scope(string id)
{
    try { return scope_ptr->symbols.at(id); }
    catch(out_of_range) { return NULL; } 
}

int symbol_table::add_symbol(string id, symbol* sym)
{
    scope_ptr->symbols[id] = sym;
    return 0;
}

int symbol_table::remove_symbol(string id)
{
    scope_ptr->symbols.erase(id);
}

void symbol_table::push_scope()
{
    scope* child = new scope;
    child->outer_scope = scope_ptr;
    scope_ptr = child;
    scope_level++;
}

void symbol_table::pop_scope()
{
    if(scope_level == 0) return;

    for(map<string, symbol*>::iterator it = scope_ptr->symbols.begin(); it != scope_ptr->symbols.end(); it++)
    {
        delete it->second;
    }

    scope_ptr->symbols.clear();
    scope* temp = scope_ptr;
    scope_ptr = scope_ptr->outer_scope;
    delete temp;
    scope_level--;
}