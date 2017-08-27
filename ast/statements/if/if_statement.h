#ifndef IF_STATEMENT
#define IF_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

class if_statement : public statement
{
private:
    expression* condition;
    statement *true_block, *false_block;

public:
    if_statement(int position, expression* condition, statement* true_block, statement* false_block) :
    statement(position)
    {
        this->condition = condition;
        this->true_block = true_block;
        this->false_block = false_block;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic;
};

#endif // IF_STATEMENT