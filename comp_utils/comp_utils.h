#ifndef COMP_UTILS
#define COMP_UTILS

#include <stdlib.h>
#include <string>
#include "colors.h"

using namespace std;

class comp_utils
{
public:
    void static show_message(string type, string msg, int position);
};

#endif // COMP_UTILS