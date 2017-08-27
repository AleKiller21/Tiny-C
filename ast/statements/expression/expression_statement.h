#ifndef EXPRESSION_STATEMENT
#define EXPRESSION_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class expression_statement : public statement
{
private:
    expression* expr;

public:
    expression_statement(int position, expression* expr) : statement(position)
    {
        this->expr = expr;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // EXPRESSION_STATEMENT