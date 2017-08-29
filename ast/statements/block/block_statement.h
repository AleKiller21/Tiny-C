#ifndef BLOCK_STATEMENT
#define BLOCK_STATEMENT

#include "../statement.h"
#include "../../declarations/declaration_list/declaration_list.h"

class block_statement : public statement
{
private:
    statement* stmt_list;
    declaration_list* decl_list;

public:
    block_statement(statement* stmts, declaration_list* decls) : statement(0)
    {
        stmt_list = stmts;
        decl_list = decls;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // BLOCK_STATEMENT