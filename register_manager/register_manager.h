#ifndef REGISTER_MANAGER
#define REGISTER_MANAGER

#include <string>
#include <stdexcept>
#include <map>
#include <vector>

using namespace std;

class register_manager
{
private:
    map<string, bool> temp_regs;
    map<string, bool> saved_regs;
    map<string, string> sregs_asked;
    int sregs_used;

public:
    register_manager();
    int get_sregs_used();
    string get_register(bool preserved);
    void free_register(string reg);
    void reset_sregisters();
};

#endif