#include "declaration.h"

declaration::declaration(declarator_list* decls, int type)
{
    declarators = decls;
    this->type = type;
    declarators->set_type(type);
}

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