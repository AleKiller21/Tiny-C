#ifndef WHILE_STATEMENT
#define WHILE_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class while_statement : public statement
{
private:
    expression* condition;
    statement* stmt;

public:
    while_statement(expression* expr, statement* stmt, int position) : statement(position)
    {
        condition = expr;
        this->stmt = stmt;
    }

    string to_string();
    int get_kind();
    // string generate_mips();
    // void validate_semantic();
};

#endif // WHILE_STATEMENT