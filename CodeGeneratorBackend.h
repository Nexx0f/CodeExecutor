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
    
    Instruction instCmpRegReg;
    Instruction instSeteReg;
    Instruction instSetneReg;
    Instruction instSetgReg;
    Instruction instSetgeReg;
    Instruction instSetlReg;
    Instruction instSetleReg;
    
    Instruction instAddRegReg;
    Instruction instSubRegReg;
    Instruction instImulReg;
    Instruction instIdivReg;
    Instruction instCdqe;
    
    Instruction instRet;
    
public:
    CodeGeneratorBackend ();  
   ~CodeGeneratorBackend ();
    
    void        emitMov   (GPReg dest, GPReg     src);
    void        emitMov   (GPReg dest, sysint_t  src);
    void        emitMov   (GPReg dest, sysuint_t src);
    
    void        emitPush  (GPReg     dest);
    void        emitPush  (sysint_t  dest);
    void        emitPush  (sysuint_t dest);
    
    void        emitPop   (GPReg dest);
    
    void        emitCmp   (GPReg dest, GPReg src);
    void        emitSete  (GPReg dest);
    void        emitSetne (GPReg dest);
    void        emitSetg  (GPReg dest);
    void        emitSetge (GPReg dest);
    void        emitSetl  (GPReg dest);
    void        emitSetle (GPReg dest);
    
    void        emitAdd   (GPReg dest, GPReg src);
    void        emitSub   (GPReg dest, GPReg src);
    void        emitImul   (GPReg dest);
    void        emitIdiv  (GPReg dest);
    void        emitCdqe  ();
    
    void        emitRet   ();
    
    ResFunction make     ();
};

#endif
