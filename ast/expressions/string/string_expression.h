#ifndef STRING_EXPRESSION
#define STRING_EXPRESSION

#include "../expression.h"

class string_expression : public expression
{
private:
    string value;

public:
    string_expression(string* value);
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // STRING_EXPRESSION