#ifndef ID
#define ID

#include "../../expression.h"

class id_expression : public expression
{
private:
    string lexeme;

public:
    id_expression(string* lexeme, int position) : expression(position)
    {
        this->lexeme = *lexeme;
        delete lexeme;
        lvalue = true;
    }
    
    string to_string();
    string get_lexeme();
    id_attributes get_type();
    int get_kind();
    // string generate_mips();
};

#endif // ID