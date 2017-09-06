#ifndef COMP_UTILS
#define COMP_UTILS

#include <stdlib.h>
#include <string>
#include "colors.h"
#include "../ast/types.h"

using namespace std;

extern int semantic_errors;

class comp_utils
{
public:
    void static show_message(string type, string msg, int position);
    string static get_type_lexeme(int type);
};

#endif // COMP_UTILS