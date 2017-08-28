#include "parameter_list.h"

string parameter_list::to_string()
{
    string str;
    for(list<parameter_declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        str += (*it)->to_string() + ", ";
    }
}

void parameter_list::add_param(parameter_declarator* param)
{
    params.push_back(param);
}