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

string comp_utils::get_type_lexeme(int type)
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