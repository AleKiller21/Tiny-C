#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"

using namespace std;

class declarator
{
private:
    int position;

public:
    bool pointer;
    int type;

    virtual string to_string() = 0;
    virtual string generate_mips() { throw "function not yet implemented"; }
    virtual void validate_semantic() { throw "function not yet implemented"; }

protected:
    declarator(int position)
    {
        this->position = position;
        pointer = false;
    }
};

#endif // DECLARATOR