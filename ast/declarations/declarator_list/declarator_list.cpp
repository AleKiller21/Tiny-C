#include "declarator_list.h"

void declarator_list::add_declarator(declarator* decl)
{
    declarators.push_back(decl);
}

void declarator_list::set_type(int type)
{
    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        (*it)->type = type;
    }
}

void declarator_list::validate_semantic()
{
    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        (*it)->validate_semantic();
        declarator_pos++;
    }
}

string declarator_list::to_string()
{
    string str;

    if(declarators.size() == 1) return (*declarators.begin())->to_string();

    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        str += (*it)->to_string() + ", ";
    }

    return str;
}

string* declarator_list::generate_code(stack_manager *manager)
{
    string code;

    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        string *decl_code = (*it)->generate_code(manager);
        code += *decl_code;
        delete decl_code;
    }

    return new string(code);
}

list<stack_entry>* declarator_list::create_stack_entries()
{
    list<stack_entry> *decl_entries = new list<stack_entry>();
    list<declarator*>::iterator it = declarators.begin();
    
    for(; it != declarators.end(); it++)
    {
        stack_entry *entry = (*it)->create_stack_entry();
        if(entry != NULL)
        {
            decl_entries->push_back(*entry);
            delete entry;
        }
    }

    return decl_entries;
}