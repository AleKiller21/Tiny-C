#include "declarator_list.h"

void declarator_list::add_declarator(declarator* decl)
{
    declarators.push_back(decl);
}

string declarator_list::to_string()
{
    string str;

    if(declarators.size() == 1) return (*declarators.begin())->to_string();

    for(list<declarator*>::iterator it = declarators.begin(); it != declarators.end(); it++)
    {
        //if(it + 1 == declarators.end()) return str + (*it)->to_string();
        str += (*it)->to_string() + ", ";
    }

    return str;
}