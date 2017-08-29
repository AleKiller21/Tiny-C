#include "function_definition.h"

function_definition::function_definition(int type, declarator* decl, statement* stmt)
{
    this->type = type;
    this->decl = decl;
    this->stmt = stmt;
}

string function_definition::to_string()
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

    return str + decl->to_string() + "\n" + stmt->to_string();
}