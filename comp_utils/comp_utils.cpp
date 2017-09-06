#include "comp_utils.h"

void comp_utils::show_message(string type, string msg, int position)
{
    if(type == "error")
    {
        semantic_errors++;
        fprintf(stderr, "Line %d: " RED "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
    }
    else if(type == "warning")
        fprintf(stderr, "Line %d: " YELLOW "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
}

string comp_utils::get_id_attrs(id_attributes attrs)
{
    string result;

    switch(attrs.type)
    {
        case INT:
            result = "int";
        case CHAR:
            result = "char";
        case VOID:
            result = "void";
    }

    if(attrs.kind == ARRAY || attrs.pointer) result += "*";
    if(attrs.kind == FUNCTION) result += "f";
    return result;
}