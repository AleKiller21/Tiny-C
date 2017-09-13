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
    vector<int> saved_regs;

public:
    register_manager();
    string get_free_register(bool preserved);
    int get_sregs_used();
    void free_register(string reg);
    void push_sregs();
    void pop_sregs();
};

#endif