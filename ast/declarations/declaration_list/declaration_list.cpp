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

string* declaration_list::generate_code()
{
    return new string("");
}