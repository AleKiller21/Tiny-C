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

#endif // ASM_CODE