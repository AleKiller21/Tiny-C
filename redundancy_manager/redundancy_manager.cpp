#include "redundancy_manager.h"

void redundancy_manager::make_all_removable(string key)
{
    list<redundant_declaration>* decls = redundant_declarations[key];
    for(list<redundant_declaration>::iterator it = decls->begin(); it != decls->end(); it++)
    {
        (*it).removable = true;
    }
}

void redundancy_manager::push_declaration(string key, redundant_declaration decl)
{
    try
    {
        redundant_declarations.at(key)->push_back(decl);
    }

    catch(out_of_range)
    {
        redundant_declarations[key] = new list<redundant_declaration> { decl };
    }
}