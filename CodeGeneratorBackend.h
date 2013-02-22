#include <sys/mman.h>
#include <map>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <initializer_list>

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

typedef int64_t        sysint_t;
typedef unsigned char  GPReg;

typedef std::initializer_list<unsigned char> opcode;

class ByteData
{
public:    
    std::vector <unsigned char> bytes;

public:
    ByteData ();
   ~ByteData ();
   
    bool emitByte (unsigned char byte);
    
    template <typename T>
    void emitImmediate (T data);
    
    void emitOpcode    (opcode _opcode);
};

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
    bool emitInstruction (opcode _opcode, int rmField, GPReg dest);
    bool emitInstruction (opcode _opcode);
};