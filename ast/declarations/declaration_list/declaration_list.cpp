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
    string code;
    int stack_displacement = 0;

    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        stack_displacement += (*it)->calculate_declarators_stack_displacement();
        string *decl_code = (*it)->generate_code();
        code += *decl_code;
        delete decl_code;
    }

    if(stack_displacement % 4 != 0) stack_displacement = (stack_displacement / 4 + 1) * 4;

    code = "\taddi $sp, $sp, -" + std::to_string(stack_displacement + 4) + "\n" + code;
    return new string(code);
}