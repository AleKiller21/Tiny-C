#ifndef LABEL_MANAGER
#define LABEL_MANAGER

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class label_manager
{
public:
    map<string, int> labels;

    string get_free_label(string name);
};

#endif