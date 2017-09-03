#ifndef CHAR_EXPRESSION
#define CHAR_EXPRESSION

#include "../../expression.h"

class char_expression : public expression
{
private:
    char value;

public:
    char_expression(char value, int position) : expression(position)
    {
        this->value = value;
    }
    
    string to_string();
    int get_kind();

    // string get_type();
    // string generate_mips();
};

#endif // CHAR_EXPRESSION