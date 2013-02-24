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
        
    FILE* dump = fopen ("dump.txt", "wb");
    fwrite (memory, instructionEmitter -> byteData -> bytes.size(), 1, dump);
    fclose (dump);
    
    return reinterpret_cast <ResFunction> (memory);    
}

void CodeGeneratorBackend::emitMov(GPReg dest, GPReg src)
{
    instructionEmitter -> emitInstruction (instMovRegReg._opcode, dest, src);
}

void CodeGeneratorBackend::emitMov(GPReg dest, sysint_t src)
{
    instructionEmitter -> emitInstruction (instMovRegImm._opcode, dest, src);
}

void CodeGeneratorBackend::emitPush(GPReg dest)
{
    instructionEmitter -> emitInstruction (instPushReg._opcode, instPushReg.rmField, dest);
}

void CodeGeneratorBackend::emitPush(sysint_t dest)
{
    instructionEmitter -> emitInstruction (instPushImm._opcode, dest);
}

void CodeGeneratorBackend::emitPop(GPReg dest)
{
    instructionEmitter -> emitInstruction (instPopReg._opcode, instPopReg.rmField, dest);
}

void CodeGeneratorBackend::emitRet()
{
    instructionEmitter -> emitInstruction (instRet._opcode);
}