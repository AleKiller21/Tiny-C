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

string* declarator_list::generate_code()
{
    string code;

    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        string *decl_code = (*it)->generate_code();
        code += *decl_code;
        delete decl_code;
    }

    return new string(code);
}

int declarator_list::calculate_stack_displacement()
{
    int displacement = 0;
    list<declarator*>::iterator it = declarators.begin();

    if((*it)->is_global) return 0;
    for(; it != declarators.end(); it++) displacement += (*it)->calculate_stack_displacement();

    return displacement;
}