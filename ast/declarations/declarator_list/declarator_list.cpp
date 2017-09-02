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