#ifndef BREAK_STATEMENT
#define BREAK_STATEMENT

#include "../statement.h"

class break_statement : public statement
{
public:
    break_statement(int position) : statement(position) {}

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // BREAK_STATEMENT