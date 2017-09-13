#include "label_manager.h"

string label_manager::get_free_label(string name)
{
    try
    {
        int count = labels.at(name);
        labels[name] = count + 1;
        return name + to_string(count + 1);
    }

    catch(out_of_range)
    {
        labels[name] = 0;
        return name + "0";
    }
}