#include "CodeGeneratorBackend.h"

CodeGeneratorBackend::CodeGeneratorBackend()
{
    instructionEmitter = new InstructionEmitter;
    
    rax = 0;
    rcx = 1;
    rdx = 2;
    rbx = 3;
    rsp = 4;
    rbp = 5;
    rsi = 6;
    rdi = 7;
    
    instMovRegImm = {{0xB8}, 0};
    instMovRegReg = {{0x8B}, 0};
    
    instPushReg   = {{0xFF}, 6};
    instPushImm   = {{0x68}, 0};
    
    instPopReg    = {{0x8F}, 0};
    
    instCmpRegReg = {{0x3B}, 0};
    instSeteReg   = {{0x0F, 0x94}, 0};
    instSetneReg  = {{0x0F, 0x95}, 0};
    instSetgReg   = {{0x0F, 0x9F}, 0};
    instSetgeReg  = {{0x0F, 0x9D}, 0};
    instSetlReg   = {{0x0F, 0x9C}, 0};
    instSetleReg  = {{0x0F, 0x9E}, 0};
    
    instAddRegReg = {{0x03}, 0};
    instSubRegReg = {{0x2B}, 0};
    instImulReg   = {{0xF7}, 5};
    instIdivReg   = {{0xF7}, 7};
    instCdqe      = {{0x98}, 0};
    
    instJmpRel32  = {{0xE9}, 0};
    instJeRel32   = {{0x0F, 0x84}, 0};
    instJneRel32  = {{0x0F, 0x85}, 0};
    instJaRel32   = {{0x0F, 0x87}, 0};
    instJaeRel32  = {{0x0F, 0x83}, 0};
    instJbRel32   = {{0x0F, 0x82}, 0};
    instJbeRel32  = {{0x0F, 0x86}, 0};
    
    instCallRel32 = {{0xE8}, 0};
    instCallReg   = {{0xFF}, 2};
    
    instRet       = {{0xC3}, 0};
}

CodeGeneratorBackend::~CodeGeneratorBackend()
{

}

ResFunction CodeGeneratorBackend::make()
{
    void* memory = mmap(0, instructionEmitter -> byteData -> bytes.size(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    unsigned char* m = reinterpret_cast <unsigned char*> (memory);
        for (unsigned i = 0; i < instructionEmitter -> byteData -> bytes.size(); i++)
            m[i] = instructionEmitter -> byteData -> bytes [i];
       
    setLabelsAdresses   (m);   
    
    FILE* dump = fopen ("dump.txt", "wb");
    fwrite (memory, instructionEmitter -> byteData -> bytes.size(), 1, dump);
    fclose (dump);
    
    return reinterpret_cast <ResFunction> (memory);    
}

Label CodeGeneratorBackend::newLabel()
{
    createdLabels.push_back ({createdLabels.size()});
    return createdLabels [createdLabels.size() - 1]; 
}

void CodeGeneratorBackend::bindLabel(Label label)
{
    bindedLabels [label.labelId] = instructionEmitter -> byteData -> bytes.size();
}

void CodeGeneratorBackend::setLabelsAdresses(unsigned char* memory)
{
    std::map <int, int>::iterator currentAdr;
    for (currentAdr = labelsToJump.begin(); currentAdr != labelsToJump.end(); currentAdr++)
    {
        std::map <int, int>::const_iterator foundLabel = bindedLabels.find (currentAdr -> second);
        
        sysuint_t labelAdress = reinterpret_cast <sysuint_t> (&(memory [foundLabel -> second]));
        sysuint_t jmpAdress   = reinterpret_cast <sysuint_t> (&(memory [currentAdr -> first]));
        
        sysint32_t relativeAdress = labelAdress - jmpAdress;
        
        for (int i = 0; i < sizeof (sysint32_t); i++)
        {
            memory [currentAdr -> first - 4 + i] = reinterpret_cast <uint8_t*> (&relativeAdress) [i];
        }
    }
}

void CodeGeneratorBackend::emitMov (GPReg dest, GPReg src)
{
    instructionEmitter -> emitInstruction (instMovRegReg._opcode, dest, src);
}

void CodeGeneratorBackend::emitMov (GPReg dest, sysint_t src)
{
    instructionEmitter -> emitInstruction (instMovRegImm._opcode, dest, src);
}

void CodeGeneratorBackend::emitMov (GPReg dest, sysuint_t src)
{
    instructionEmitter -> emitInstruction (instMovRegImm._opcode, dest, src);
}

void CodeGeneratorBackend::emitPush (GPReg dest)
{
    instructionEmitter -> emitInstruction (instPushReg._opcode, instPushReg.rmField, dest);
}

void CodeGeneratorBackend::emitPush (sysint_t dest)
{
    instructionEmitter -> emitInstruction (instPushImm._opcode, dest);
}

void CodeGeneratorBackend::emitPush (sysuint_t dest)
{
    instructionEmitter -> emitInstruction (instPushImm._opcode, dest);
}

void CodeGeneratorBackend::emitPop (GPReg dest)
{
    instructionEmitter -> emitInstruction (instPopReg._opcode, instPopReg.rmField, dest);
}

void CodeGeneratorBackend::emitCmp (GPReg dest, GPReg src)
{
    instructionEmitter -> emitInstruction (instCmpRegReg._opcode, dest, src);
}

void CodeGeneratorBackend::emitSete (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSeteReg._opcode, instSeteReg.rmField, dest);
}

void CodeGeneratorBackend::emitSetne (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSetneReg._opcode, instSetneReg.rmField, dest);
}

void CodeGeneratorBackend::emitSetg (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSetgReg._opcode, instSetgReg.rmField, dest);
}

void CodeGeneratorBackend::emitSetge (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSetgeReg._opcode, instSetgeReg.rmField, dest);

}

void CodeGeneratorBackend::emitSetl (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSetlReg._opcode, instSetlReg.rmField, dest);
}

void CodeGeneratorBackend::emitSetle (GPReg dest)
{
    instructionEmitter -> emitInstruction (instSetleReg._opcode, instSetleReg.rmField, dest);
}

void CodeGeneratorBackend::emitAdd (GPReg dest, GPReg src)
{
    instructionEmitter -> emitInstruction (instAddRegReg._opcode, dest, src);
}

void CodeGeneratorBackend::emitSub (GPReg dest, GPReg src)
{
    instructionEmitter -> emitInstruction (instSubRegReg._opcode, dest, src);
}

void CodeGeneratorBackend::emitImul (GPReg dest)
{
    instructionEmitter -> emitInstruction (instImulReg._opcode, instImulReg.rmField, dest);
}

void CodeGeneratorBackend::emitIdiv (GPReg dest)
{
    instructionEmitter -> emitInstruction (instIdivReg._opcode, instIdivReg.rmField, dest);
}

void CodeGeneratorBackend::emitCdqe ()
{
    instructionEmitter -> emitInstruction (instCdqe._opcode);
}

void CodeGeneratorBackend::emitJmp (Label dest)
{
    instructionEmitter -> emitInstruction (instJmpRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJe (Label dest)
{
    instructionEmitter -> emitInstruction (instJeRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJne (Label dest)
{
    instructionEmitter -> emitInstruction (instJneRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJa (Label dest)
{
    instructionEmitter -> emitInstruction (instJaRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJae (Label dest)
{
    instructionEmitter -> emitInstruction (instJaeRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJb (Label dest)
{
    instructionEmitter -> emitInstruction (instJbRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitJbe (Label dest)
{
    instructionEmitter -> emitInstruction (instJbeRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitCall(void* dest)
{
    instructionEmitter -> emitInstruction (instMovRegImm._opcode, rdx, reinterpret_cast <sysuint_t> (dest));
    instructionEmitter -> emitInstruction (instCallReg._opcode, instCallReg.rmField, rdx);
    //instructionEmitter -> emitInstruction (instCallRel32._opcode, (sysint32_t)0);
    //adressesToJump [instructionEmitter -> byteData -> bytes.size()] = dest;
}

void CodeGeneratorBackend::emitCall(Label dest)
{
    instructionEmitter -> emitInstruction (instCallRel32._opcode, (sysint_t)0);
    labelsToJump [instructionEmitter -> byteData -> bytes.size()] = dest.labelId;
}

void CodeGeneratorBackend::emitRet ()
{
    instructionEmitter -> emitInstruction (instRet._opcode);
}