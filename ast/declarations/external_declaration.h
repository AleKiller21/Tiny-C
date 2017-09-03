#ifndef EXTERNAL_DECLARATION
#define EXTERNAL_DECLARATION

#define DECL        1
#define FUNC_DEF    2

#include "../types.h"
#include <string>

using namespace std;

class external_declaration
{
protected:
    int type;
    int category;

    external_declaration(int type, int category) { this->type = type; this->category = category; }

public:
    virtual string to_string() = 0;
    //string generate_mips() = 0;
    virtual void validate_semantic() = 0;
};

#endif // EXTERNAL_DECLARATION