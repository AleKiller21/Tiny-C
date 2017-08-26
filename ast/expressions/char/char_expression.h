#ifndef CHAR_EXPRESSION
#define CHAR_EXPRESSION

#include "../expression.h"

class char_expression : expression
{
private:
    char value;

public:
    char_expression(char value);
    string to_string();

    // string get_type();
    // string generate_mips();
};

#endif // CHAR_EXPRESSION