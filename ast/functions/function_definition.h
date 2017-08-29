#ifndef FUNCTION_DEFINITION
#define FUNCTION_DEFINITION

#include "../declarations/declarator.h"
#include "../statements/statement.h"
#include "../declarations/external_declaration.h"

class function_definition : public external_declaration
{
private:
    int type;
    declarator* decl;
    statement* stmt;

public:
    function_definition(int type, declarator* decl, statement* stmt) : external_declaration(type)
    {
        this->decl = decl;
        this->stmt = stmt;
    }
    
    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // FUNCTION_DEFINITION