#include "ByteData.h"

template <unsigned long N>
struct binary
{
    static unsigned const value = binary <N/10>::value << 1 | N%10;
};

template <>             
struct binary <0>                      
{
    static unsigned const value = 0;
};

#define BIN(a) binary<a>::value

template <unsigned long N>
struct decimal
{
    static unsigned const value = decimal <N/2>::value * 10 + N%2; 
};

template <>
struct decimal <0>
{
    static unsigned const value = 0;
};

#define DEC(a) decimal<a>::value

class InstructionEmitter
{
public:
    ByteData* byteData;
    
public:    
    InstructionEmitter (ByteData* newByteData);
    InstructionEmitter ();
   ~InstructionEmitter ();
   
    bool emitInstruction (opcode _opcode, GPReg dest,  GPReg    src); 
    bool emitInstruction (opcode _opcode, GPReg dest,  sysint_t src);
    bool emitInstruction (opcode _opcode, GPReg dest,  sysuint_t src);
    
    bool emitInstruction (opcode _opcode, int rmField, GPReg dest);
    bool emitInstruction (opcode _opcode, sysint_t   dest);
    bool emitInstruction (opcode _opcode, sysuint_t  dest);
    bool emitInstruction (opcode _opcode, sysint32_t dest);
    
    bool emitInstruction (opcode _opcode);
};