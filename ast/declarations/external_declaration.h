#ifndef EXTERNAL_DECLARATION
#define EXTERNAL_DECLARATION

#include "../types.h"
#include <string>

using namespace std;

class external_declaration
{
protected:
    int type;

    external_declaration(int type) { this->type = type; }

public:
    virtual string to_string() = 0;
    // string generate_mips();
    // void validate_semantic();
};

#endif // EXTERNAL_DECLARATION