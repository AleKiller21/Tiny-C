#ifndef FUNCTION_DEFINITION
#define FUNCTION_DEFINITION

#include "../declarations/declarator.h"
#include "../declarations/function/function_declarator.h"
#include "../statements/statement.h"
#include "../declarations/external_declaration.h"
#include "../../comp_utils/comp_utils.h"
#include <vector>

using namespace std;

extern symbol_table sym_table;
extern redundancy_manager redund_manager;

class function_definition : public external_declaration
{
private:
    declarator* decl;
    statement* stmt;

    void validate_block_semantic();

public:
    function_definition(int type, declarator* decl, statement* stmt) : external_declaration(type, FUNC_DEF)
    {
        this->decl = decl;
        this->decl->type = type;
        this->stmt = stmt;
    }
    
    string to_string();
    // string generate_mips();
    void validate_semantic();
};

#endif // FUNCTION_DEFINITION