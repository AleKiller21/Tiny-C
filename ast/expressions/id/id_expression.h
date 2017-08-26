#ifndef ID
#define ID

#include "../expression.h"

class id_expression : public expression
{
private:
    string lexeme;

public:
    id_expression(string* lexeme, int position) : expression(position)
    {
        this->lexeme = *lexeme;
        delete lexeme;
    }
    
    string to_string();

    // string get_type();
    // string generate_mips();
};

#endif // ID