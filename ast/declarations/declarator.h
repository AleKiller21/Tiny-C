#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"
#include "initializer/initializer.h"
#include "../expressions/primary/id/id_expression.h"

using namespace std;

class declarator
{
private:
    int position;

public:
    initializer* init;
    id_expression* id_expr;
    bool pointer;
    int type;

    virtual string to_string() 
    {
        if(init != NULL) return " = " + init->to_string();
        return "";
    }
    
    virtual string generate_mips() { throw "function not yet implemented"; }
    virtual void validate_semantic() { throw "function not yet implemented"; }

    void show_error(const char* msg)
    {
        fprintf(stderr, "Line %d: error: %s", position, msg);
    }

protected:
    declarator(id_expression* id, int position)
    {
        this->position = position;
        id_expr = id;
        pointer = false;
        init = NULL;
    }
};

#endif // DECLARATOR