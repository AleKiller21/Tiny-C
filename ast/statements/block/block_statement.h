#ifndef BLOCK_STATEMENT
#define BLOCK_STATEMENT

#include "../statement.h"
#include "../list/statement_list.h"
#include "../../declarations/declaration_list/declaration_list.h"

class block_statement : public statement
{
private:
    statement* stmt_list;
    declaration_list* decl_list;

public:
    bool first_class_block;

    block_statement(statement* stmts, declaration_list* decls) : statement(0)
    {
        stmt_list = stmts;
        decl_list = decls;
        first_class_block = false;
    }

    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager, string nearest_loop, string nearest_loop_end);
    void validate_semantic(bool is_loop_statement, bool *has_return);
    void push_statement(statement* stmt);
};

#endif // BLOCK_STATEMENT