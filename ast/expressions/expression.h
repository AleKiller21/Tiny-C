#ifndef EXPRESSION
#define EXPRESSION

#include <string>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include "../../comp_utils/comp_utils.h"
#include "../../symbol_table/symbol_table.h"
#include "../../asm_code/asm_code.h"
#include "../../stack_manager/stack_manager.h"
#include "../../register_manager/register_manager.h"
#include "../../label_manager/label_manager.h"
#include "../id_attributes.h"
#include "../id_kind.h"
#include "../types.h"

#define ID_EXPR         1
#define CHAR_EXPR       2
#define INT_EXPR        3
#define STRING_EXPR     4
#define ARRAY_EXPR      5
#define FUNCTION_EXPR   6
#define POST_INC_EXPR   7
#define POST_DEC_EXPR   8
#define PRE_INC_EXPR    9
#define PRE_DEC_EXPR    10
#define POINTER_EXPR    11
#define ADDRESS_EXPR    12
#define POSITIVE_EXPR   13
#define NEGATIVE_EXPR   14
#define TWO_COMP_EXPR   15
#define NEGATION_EXPR   16
#define SIZEOF_EXPR     17
#define PRINTF_EXPR     18
#define SCANF_EXPR      19
#define CAST_EXPR       20
#define MULT_EXPR       21
#define DIV_EXPR        22
#define MOD_EXPR        23
#define SUM_EXPR        24
#define SUB_EXPR        25
#define LSHIFT_EXPR     26
#define RSHIFT_EXPR     27
#define LT_EXPR         28
#define GT_EXPR         29
#define LE_EXPR         30
#define GE_EXPR         31
#define EQUAL_EXPR      32
#define NE_EXPR         33
#define AND_EXPR        34
#define XOR_EXPR        35
#define OR_EXPR         36
#define LA_EXPR         37
#define LO_EXPR         38
#define COND_EXPR       39
#define ASSIGN_EXPR     40
#define LIST_EXPR       41
#define TIME_EXPR       42
#define SRAND_EXPR      43
#define RAND_EXPR       44

using namespace std;

extern symbol_table sym_table;
extern register_manager reg_manager;
extern label_manager lbl_manager;

class expression
{
protected:
    int position;
    bool lvalue;

public:
    bool is_code;

    expression(int position) { this->position = position; lvalue = false; }
        
    virtual id_attributes get_type() { throw "not implemented exception"; }
    virtual asm_code *generate_code(stack_manager *manager) { printf("expression generate_code not implemented."); return NULL; }
    virtual string *get_operand_id() { return NULL; }
    virtual string to_string() = 0;
    virtual int get_kind() = 0;
    bool get_lvalue() { return lvalue; }

    bool is_compound_expression()
    {
        switch(get_kind())
        {
            case MULT_EXPR: case DIV_EXPR: case MOD_EXPR: case SUM_EXPR: case SUB_EXPR: case LSHIFT_EXPR: case RSHIFT_EXPR:
            case LT_EXPR: case GT_EXPR: case LE_EXPR: case GE_EXPR: case EQUAL_EXPR: case NE_EXPR: case AND_EXPR:
            case XOR_EXPR: case OR_EXPR: case LA_EXPR: case LO_EXPR: case ASSIGN_EXPR: case FUNCTION_EXPR: case SIZEOF_EXPR:
            case PRINTF_EXPR: case RAND_EXPR:
                return true;
            default:
                return false;
        }
    }
};

#endif // EXPRESSION