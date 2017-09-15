#ifndef ASM_CODE
#define ASM_CODE

#define WORD    ".word"
#define BYTE    ".byte"
#define ASCIIZ  ".asciiz"

#include <string>

using namespace std;

struct asm_code
{
    string code;
    string place;
    int constant;
};

struct stack_entry
{
    string asm_type;
    string var_id;
    int byte_offset;
};

#endif // ASM_CODE