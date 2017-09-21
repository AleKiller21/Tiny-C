#include "declaration_list.h"

void declaration_list::add_declaration(declaration* decl)
{
    declarations.push_back(decl);
}

string declaration_list::to_string()
{
    string str;
    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        str += "\t" + (*it)->to_string();
    }

    return str;
}

void declaration_list::validate_semantic()
{
    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        (*it)->validate_semantic();
    }
}

string* declaration_list::generate_code(stack_manager *manager)
{
    map<string, stack_entry> entries;
    string code = map_variables_to_stack(manager);

    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        string *decl_code = (*it)->generate_code(manager);
        code += *decl_code;
        delete decl_code;
    }

    return new string(code);
}

string declaration_list::map_variables_to_stack(stack_manager *manager)
{
    string code;

    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        list<stack_entry> *decls = (*it)->create_stack_entries();

        for(list<stack_entry>::iterator it = decls->begin(); it != decls->end(); it++)
        {
            string id = (*it).var_id;
            manager->vars[id] = *it;

            if(manager->vars[id].asm_type == WORD)
                while(manager->current_byte_offset % 4 != 0) manager->current_byte_offset++;

            manager->vars[id].byte_offset = manager->current_byte_offset;
            manager->current_byte_offset += (*it).size;
        }

        decls->clear();
        delete decls;
    }

    return code;
}