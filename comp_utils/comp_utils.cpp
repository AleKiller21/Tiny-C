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

string comp_utils::id_attrs_to_string(id_attributes attrs)
{
    string result;

    switch(attrs.type)
    {
        case INT:
            result = "int";
            break;
        case CHAR:
            result = "char";
            break;
        case VOID:
            result = "void";
            break;
    }

    if(attrs.kind == ARRAY || attrs.pointer) result += "*";
    if(attrs.kind == FUNCTION) result += "f";
    return result;
}

bool comp_utils::is_type_int(id_attributes attrs)
{
    return attrs.type == INT;
}

bool comp_utils::is_type_char(id_attributes attrs)
{
    return attrs.type == CHAR;
}

bool comp_utils::is_type_void(id_attributes attrs)
{
    return attrs.type == VOID;
}