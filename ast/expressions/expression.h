#ifndef EXPRESSION
#define EXPRESSION

#include <string>
#include <cstdio>
#include <stdexcept>
#include <iostream>

using namespace std;

class expression
{
public:
    bool lvalue;

    virtual string get_type() { throw "Function has not been implemented"; }
    virtual string generate_mips() { throw "Function has not been implemented"; }
    virtual string to_string() = 0;

    void show_error(const char* msg)
    {
        extern int yylineno;
        fprintf(stderr, "Line %d: error: %s", yylineno, msg);
    }
};

#endif // EXPRESSION