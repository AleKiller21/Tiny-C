#ifndef EXPRESSION
#define EXPRESSION

#include <string>
#include <cstdio>
#include <stdexcept>
#include <iostream>

using namespace std;

class expression
{
private:
    int position;

public:
    bool lvalue;

    expression(int position) { lvalue = false; this->position = position; }
    
    virtual string get_type() { throw "Function has not been implemented"; }
    virtual string generate_mips() { throw "Function has not been implemented"; }
    virtual string to_string() = 0;

    void show_error(const char* msg)
    {
        fprintf(stderr, "Line %d: error: %s", position, msg);
    }
};

#endif // EXPRESSION