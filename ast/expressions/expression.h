#ifndef EXPRESSION
#define EXPRESSION

#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

class expression
{
protected:
    virtual string get_type() { throw "Function has not been implemented"; }
    virtual string generate_mips() { throw "Function has not been implemented"; }

public:
    void show_error(const char* msg)
    {
        extern int yylineno;
        fprintf(stderr, "Line %d: error: %s", yylineno, msg);
    }
};

#endif // EXPRESSION