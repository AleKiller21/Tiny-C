#ifndef EXTERNAL_DECLARATION
#define EXTERNAL_DECLARATION

#define DECL        1
#define FUNC_DEF    2

#include "../types.h"
#include "../../label_manager/label_manager.h"
#include "../../register_manager/register_manager.h"
#include "../../stack_manager/stack_manager.h"
#include <string>

using namespace std;

extern register_manager reg_manager;
extern label_manager lbl_manager;

class external_declaration
{
protected:
    int type;
    int category;

    external_declaration(int type, int category) { this->type = type; this->category = category; }

public:
    virtual string to_string() = 0;
    virtual string *generate_code() { return new string(); }
    virtual string *generate_code(stack_manager *manager) { return new string(); }
    virtual void validate_semantic() = 0;
};

#endif // EXTERNAL_DECLARATION