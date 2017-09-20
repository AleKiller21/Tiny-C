#ifndef WHILE_STATEMENT
#define WHILE_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class while_statement : public statement
{
private:
    expression* condition;
    statement* block;

public:
    while_statement(expression* expr, statement* block, int position) : statement(position)
    {
        condition = expr;
        this->block = block;
    }

    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // WHILE_STATEMENT