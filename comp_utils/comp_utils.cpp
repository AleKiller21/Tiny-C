#include "comp_utils.h"

void comp_utils::show_message(string type, string msg, int position)
{
    if(type == "error")
        fprintf(stderr, "Line %d: " RED "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
    else if(type == "warning")
        fprintf(stderr, "Line %d: " YELLOW "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
}