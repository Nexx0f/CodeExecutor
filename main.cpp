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
    
    CodeGeneratorBackend assembler;
    
    assembler.emitPush ((sysint_t)191);
    assembler.emitPop  (assembler.rax);
    assembler.emitMov  (assembler.rcx, (sysint_t)191);
    assembler.emitMov  (assembler.rax, assembler.rcx);
    assembler.emitRet  ();
    
    ResFunction f = assembler.make();
    
    return 0;
}
