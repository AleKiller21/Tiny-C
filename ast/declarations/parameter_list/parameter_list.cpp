#include "parameter_list.h"

string parameter_list::to_string()
{
    string str;
    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        str += (*it)->to_string() + ", ";
    }
}

void parameter_list::add_param(declarator* param)
{
    params.push_back(param);
}