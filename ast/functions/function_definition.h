#ifndef FUNCTION_DEFINITION
#define FUNCTION_DEFINITION

#include "../declarations/declarator.h"
#include "../declarations/function/function_declarator.h"
#include "../statements/block/block_statement.h"
#include "../statements/return/return_statement.h"
#include "../declarations/external_declaration.h"
#include "../../comp_utils/comp_utils.h"
#include "../../stack_manager/stack_manager.h"
#include "../../register_manager/register_manager.h"
#include <vector>
#include <iostream>

using namespace std;

extern symbol_table sym_table;
extern redundancy_manager redund_manager;
extern register_manager reg_manager;
extern bool main_flag;

class function_definition : public external_declaration
{
private:
    declarator *decl;
    block_statement *block;
    stack_manager *stck_manager;

    void validate_block_semantic();

public:
    function_definition(int type, declarator* decl, statement* stmt) : external_declaration(type, FUNC_DEF)
    {
        this->decl = decl;
        this->decl->type = type;
        this->block = (block_statement*)stmt;
        this->block->first_class_block = true;
        this->stck_manager = new stack_manager();
    }
    
    string to_string();
    string *generate_code();
    void validate_semantic();
};

#endif // FUNCTION_DEFINITION