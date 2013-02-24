#include <initializer_list>
#include <stdint.h>

typedef int64_t        sysint_t;
typedef uint64_t       sysuint_t;
typedef unsigned char  GPReg;

typedef std::initializer_list<unsigned char> opcode;

struct Label
{
    int cellNumber;
};


struct Instruction
{
    opcode _opcode;
    int rmField;
};

typedef int (*ResFunction)();