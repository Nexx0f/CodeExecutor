#include <iostream>
//#include "codeblock.h"
#include "CodeGeneratorBackend.h"
#include <sys/mman.h>
#include <vector>
#include <stdio.h>

int main(int argc, char **argv) 
{
   // CodeBlock* a = new CodeBlock;
   // resultFunction x = a -> LoadBlock ("ptrTest.txt").InitExecutor(new Executor).Execute();
   // printf ("\nFunction was created!\nJit compilated function's output:\n");
    //x ();
    //printf ("\nI quit from the generated function.\n");         
   // int desired_size = 1024;
    
    InstructionEmitter codeGen;
    //codeGen.byteData -> emitByte (0xFF);
    //codeGen.byteData -> emitByte (BIN (11110000));
    codeGen.emitInstruction ({ 0xFF },        6, (GPReg)0);
    codeGen.emitInstruction ({ 0x8F },        0, (GPReg)0);
    codeGen.emitInstruction ({ 0xB8 }, (GPReg)3, (sysint_t)191);
    codeGen.emitInstruction ({ 0x8B }, (GPReg)0, (GPReg)3);
    codeGen.emitInstruction ({ 0xB8 }, (GPReg)0, (sysint_t)-50);
    codeGen.emitInstruction ({ 0x03 }, (GPReg)0, (GPReg)1);
    codeGen.emitInstruction ({ 0xC3 });
    //emit (BIN(1001000));
   // emit (0xB8);
   // emit (0xBF);
   //emit (0x00);
    //emit (0x00);
    //emit (0x00);
    //emit (0x00);
    //emit (0x00);
    //emit (0x00);
    //emit (0x00);
    //emit (0xC3);
    
    // allocate
    void* memory = mmap(0, codeGen.byteData -> bytes.size(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    //memcpy();
    unsigned char* m = reinterpret_cast <unsigned char*> (memory);
    for (unsigned i = 0; i < codeGen.byteData -> bytes.size(); i++)
        m[i] = codeGen.byteData -> bytes [i];
    /*[0] = (unsigned char)0xB8;
    m[1] = (unsigned char)0xBF;
    m[2] = (unsigned char)0x00;
    m[3] = (unsigned char)0x00;
    m[4] = (unsigned char)0x00;
    m[5] = (unsigned char)0xC3;*/
    typedef int (*F)();
    F f = reinterpret_cast <F> (memory);
    
    // deallocate
    
    
    FILE* dump = fopen ("dump.txt", "wb");
    fwrite (memory, codeGen.byteData -> bytes.size(), 1, dump);
    fclose (dump);
    
    int result = f();
    printf ("%i\n", result);    
    
    munmap(memory, codeGen.byteData -> bytes.size());
    
    return 0;
}
