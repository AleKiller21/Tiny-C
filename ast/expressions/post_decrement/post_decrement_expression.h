#ifndef POST_DECREMENT_EXPRESSION
#define POST_DECREMENT_EXPRESSION

#include "../expression.h"

class post_decrement_expression : public expression
{
private:
    expression* expr;

public:
    post_decrement_expression(expression* expr, int position) : expression(position)
    {
        this->expr = expr;
    }
    
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // POST_DECREMENT_EXPRESSION