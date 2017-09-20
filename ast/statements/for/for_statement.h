#ifndef FOR_STATEMENT
#define FOR_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class for_statement : public statement
{
private:
    statement *expr1, *block;
    expression *expr2, *expr3;

public:
    for_statement(int position, statement* block, statement* expr1, expression* expr2, expression* expr3) :
    statement(position)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->expr3 = expr3;
        this->block = block;
    }

    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // FOR_STATEMENT