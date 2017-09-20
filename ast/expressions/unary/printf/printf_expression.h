#ifndef PRINTF_EXPRESSION
#define PRINTF_EXPRESSION

#include "../unary_expression.h"
#include "../../expression_list/expression_list.h"
#include "../../primary/string/string_expression.h"
#include "../../../../compiler/compiler.h"
#include "../../../types.h"
#include <map>

class printf_expression : public unary_expression
{
private:
    vector<string> parse_string();
    vector<int> formats;

public:
    printf_expression(expression* args, int position) : unary_expression(args, position) { is_code = true; }
    string to_string();
    int get_kind();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // PRINTF_EXPRESSION