#ifndef STATEMENT
#define STATEMENT

#include <cstdio>
#include <stdexcept>
#include <string>
#include "../../symbol_table/symbol_table.h"
#include "../../comp_utils/comp_utils.h"
#include "../../stack_manager/stack_manager.h"
#include "../../label_manager/label_manager.h"
#include "../../register_manager/register_manager.h"

extern symbol_table sym_table;
extern label_manager lbl_manager;
extern register_manager reg_manager;

#define BLOCK_STMT      1
#define BREAK_STMT      2
#define CONTINUE_STMT   3
#define EXPRESSION_STMT 4
#define FOR_STMT        5
#define IF_STMT         6
#define LIST_STMT       7
#define RETURN_STMT     8
#define WHILE_STMT      9

using namespace std;

class statement
{
protected:
    int position;

public:
    statement(int position) { this->position = position; }

    virtual void validate_semantic(bool is_loop_statement, bool *has_return) = 0;
    virtual string *generate_code(stack_manager *manager) { throw "statement generate_code not implemented"; }
    virtual string to_string() = 0;
    virtual int get_kind() = 0;
};

#endif // STATEMENT