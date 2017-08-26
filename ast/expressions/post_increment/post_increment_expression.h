#ifndef POST_INCREMENT_EXPRESSION
#define POST_INCREMENT_EXPRESSION

#include "../expression.h"

class post_increment_expression : public expression
{
private:
    expression* expr;

public:
    post_increment_expression(expression* expr);
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // POST_INCREMENT_EXPRESSION