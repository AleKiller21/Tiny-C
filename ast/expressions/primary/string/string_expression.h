#ifndef STRING_EXPRESSION
#define STRING_EXPRESSION

#include "../../expression.h"

class string_expression : public expression
{
private:
    string value;

public:
    string_expression(string* value, int position) : expression(position)
    {
        this->value = *value;
        delete value;
    }
    
    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // STRING_EXPRESSION