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
    InstructionEmitter*    instructionEmitter;
    
    std::vector <Label>    createdLabels; 
    /* ^ Need to create different ID for every label */
    
    std::map    <int, int> bindedLabels;  
    /* ^ Key  - labels ID, 
     * | Data - number of byte where label stays */
    
    std::map    <int, int> labelsToJump;  
    /* ^ Key  - number of byte where adress have to be written
     * | Data - ID of label which adress have to be written */
    
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
    
    Instruction instJmpReg;
    
    Instruction instRet;
    
public:
    CodeGeneratorBackend ();  
   ~CodeGeneratorBackend ();
   
    void        setLabelsAdresses (unsigned char *memory);
    
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
    void        emitImul  (GPReg dest);
    void        emitIdiv  (GPReg dest);
    void        emitCdqe  ();
    
    void        emitJmp   (Label dest);
    void        emitRet   ();
    
    Label       newLabel  ();
    void        bindLabel (Label label);
    
    ResFunction make      ();
};

#endif
