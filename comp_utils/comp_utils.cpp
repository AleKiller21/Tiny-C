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
    string result = comp_utils::type_to_string(attrs.type);

    if(attrs.kind == ARRAY || attrs.pointer) result += "*";
    if(attrs.kind == FUNCTION) result += "f";
    return result;
}

string comp_utils::type_to_string(int type)
{
    switch(type)
    {
        case INT:
            return "int";
        case CHAR:
            return "char";
        case VOID:
            return "void";
    }
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