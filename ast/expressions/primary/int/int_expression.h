#ifndef INT_EXPRESSION
#define INT_EXPRESSION

#include "../../expression.h"

class int_expression : public expression
{
private:
    int value;
    char format;

public:
    int_expression(int value, char format, int position) : expression(position)
    {
        this->value = value;
        this->format = format;
    }
    
    char get_format();
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // INT_EXPRESSION