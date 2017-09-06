#ifndef COMP_UTILS
#define COMP_UTILS

#include <stdlib.h>
#include <string>
#include "colors.h"
#include "../ast/types.h"
#include "../ast/id_attributes.h"
#include "../ast/id_kind.h"

using namespace std;

extern int semantic_errors;

class comp_utils
{
public:
    void static show_message(string type, string msg, int position);
    string static get_id_attrs(id_attributes attrs);
};

#endif // COMP_UTILS