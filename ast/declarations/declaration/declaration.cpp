#include "declaration.h"

string declaration::to_string()
{
    string str;
    switch(type)
    {
        case INT:
            str = "int ";
            break;
        case CHAR:
            str = "char ";
            break;
        case VOID:
            str = "void ";
            break;
    }

    return str + declarators->to_string() + ";\n";
}

void declaration::validate_semantic()
{
    declarators->validate_semantic();
}

string* declaration::generate_code(stack_manager *manager)
{
    return declarators->generate_code(manager);
}

list<stack_entry>* declaration::create_stack_entries()
{
    return declarators->create_stack_entries();
}