#ifndef CONTINUE_STATEMENT
#define CONTINUE_STATEMENT

#include "../statement.h"

class continue_statement : public statement
{
public:
    continue_statement(int position) : statement(position) {}
    
    string to_string();
    int get_kind();
    // string generate_mips();
    // void validate_semantic();
};

#endif // CONTINUE_STATEMENT