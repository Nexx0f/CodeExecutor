#ifndef H_CODE_GENERATOR_BACKEND
#define H_CODE_GENERATOR_BACKEND

#include <sys/mman.h>
#include <map>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "InstructionEmitter.h"

class CodeGeneratorBackend
{
public:
    InstructionEmitter* instructionEmitter;
    
    GPReg rax;
    GPReg rcx;
    GPReg rdx;
    GPReg rbx;
    GPReg rsp;
    GPReg rbp;
    GPReg rsi;
    GPReg rdi;

    Instruction instMovRegImm;    
    Instruction instMovRegReg;
    
    Instruction instPushReg;
    Instruction instPushImm; 
    
    Instruction instPopReg;
    
    Instruction instRet;
    
public:
    CodeGeneratorBackend ();  
   ~CodeGeneratorBackend ();
    
    void        emitMov  (GPReg dest, GPReg    src);
    void        emitMov  (GPReg dest, sysint_t src);
    
    void        emitPush (GPReg    dest);
    void        emitPush (sysint_t dest);
    
    void        emitPop  (GPReg dest);
    
    void        emitRet  ();
    
    ResFunction make     ();
};

#endif
