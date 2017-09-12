#ifndef FUNCTION_DEFINITION
#define FUNCTION_DEFINITION

#include "../declarations/declarator.h"
#include "../declarations/function/function_declarator.h"
#include "../statements/block/block_statement.h"
#include "../declarations/external_declaration.h"
#include "../../comp_utils/comp_utils.h"
#include <vector>

using namespace std;

extern symbol_table sym_table;
extern redundancy_manager redund_manager;
extern bool main_flag;

class function_definition : public external_declaration
{
private:
    declarator* decl;
    block_statement* stmt;

    void validate_block_semantic();

public:
    function_definition(int type, declarator* decl, statement* stmt) : external_declaration(type, FUNC_DEF)
    {
        this->decl = decl;
        this->decl->type = type;
        this->stmt = (block_statement*)stmt;
        this->stmt->first_class_block = true;
    }
    
    string to_string();
    // string generate_mips();
    void validate_semantic();
};

#endif // FUNCTION_DEFINITION