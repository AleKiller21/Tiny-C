#include "parameter_list.h"

string parameter_list::to_string()
{
    string str;
    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        switch((*it)->type)
        {
            case INT:
                str += "int ";
                break;
            case CHAR:
                str += "char ";
                break;
            case VOID:
                str += "void ";
                break;
        }
        
        str += (*it)->to_string() + ", ";
    }

    return str;
}

void parameter_list::add_param(declarator* param)
{
    params.push_back(param);
}