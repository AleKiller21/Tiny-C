#ifndef FOR_STATEMENT
#define FOR_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class for_statement : public statement
{
private:
    statement *expr1, *expr2, *stmt;
    expression* expr3;

public:
    for_statement(int position, statement* stmt, statement* expr1, statement* expr2, expression* expr3) :
    statement(position)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->expr3 = expr3;
        this->stmt = stmt;
    }

    string to_string();
    int get_kind();
    // string generate_mips();
    // void validate_semantic();
};

#endif // FOR_STATEMENT