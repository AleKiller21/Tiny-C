#ifndef FUNCTION_DEFINITION
#define FUNCTION_DEFINITION

#include "../types.h"
#include "../declarations/declarator.h"
#include "../statements/statement.h"

class function_definition
{
private:
    int type;
    declarator* decl;
    statement* stmt;

public:
    function_definition(int type, declarator* decl, statement* stmt);
    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // FUNCTION_DEFINITION