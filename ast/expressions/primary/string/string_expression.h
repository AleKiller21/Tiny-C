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
        lvalue = false;
        delete value;
    }
    
    string to_string();
    string get_lexeme();
    int get_kind();
    type_attributes get_type();
    // string generate_mips(); TODO: generar codigo de strings
};

#endif // STRING_EXPRESSION