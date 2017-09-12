#ifndef RETURN_STATEMENT
#define RETURN_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class return_statement : public statement
{
private:
    expression* expr;

public:
    return_statement(int position, expression* expr) : statement(position) { this->expr = expr; }

    string to_string();
    int get_kind();
    // string generate_mips();
    void validate_semantic(bool is_loop_statement);
};

#endif // RETURN_STATEMENT