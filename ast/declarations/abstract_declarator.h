#ifndef ABSTRACT_DECLARATOR
#define ABSTRACT_DECLARATOR

#include "../types.h"

class abstract_declarator
{
public:
    int type;
    bool pointer;

    abstract_declarator(int type, bool pointer)
    {
        this->type = type;
        this->pointer = pointer;
    }

    string to_string()
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

        if(pointer) return str + "*";
        return str;
    }
};

#endif // ABSTRACT_DECLARATOR