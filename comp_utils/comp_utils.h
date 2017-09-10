#ifndef COMP_UTILS
#define COMP_UTILS

#include <stdlib.h>
#include <string>
#include <iostream>
#include "colors.h"
#include "../ast/types.h"
#include "../ast/id_attributes.h"
#include "../ast/id_kind.h"

using namespace std;

extern int semantic_errors;

class comp_utils
{
public:
    static void show_message(string type, string msg, int position);
    static string id_attrs_to_string(id_attributes attrs);
    static bool is_type_int(id_attributes attrs);
    static bool is_type_char(id_attributes attrs);
    static bool is_type_void(id_attributes attrs);
    static bool is_pointer(id_attributes attrs);
    static id_attributes string_to_id_attrs(string attrs);
};

#endif // COMP_UTILS