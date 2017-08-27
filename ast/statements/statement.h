#ifndef STATEMENT
#define STATEMENT

#include <cstdio>
#include <stdexcept>
#include <string>

using namespace std;

class statement
{
private:
    int position;

public:
    statement(int position) { this->position = position; }

    virtual void validate_semantic() { throw "function not yet implemented."; }
    virtual string generate_mips() { throw "function not yet implemented. "; }
    virtual string to_string() = 0;

    void show_error(const char* msg)
    {
        fprintf(stderr, "Line %d: error: %s", position, msg);
    }
};

#endif // STATEMENT