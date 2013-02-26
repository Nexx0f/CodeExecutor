#include <initializer_list>
#include <stdint.h>

typedef int64_t        sysint_t;
typedef uint64_t       sysuint_t;
typedef int32_t        sysint32_t;
typedef unsigned char  GPReg;

typedef std::initializer_list<unsigned char> opcode;

struct Label
{
    int labelId;
};


struct Instruction
{
    opcode _opcode;
    int rmField;
};

typedef int (*ResFunction)();