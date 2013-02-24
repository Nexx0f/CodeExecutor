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
    
    assembler.emitMov   (assembler.rax, (sysint_t)4100);
    assembler.emitMov   (assembler.rbx, (sysint_t)-100);
    assembler.emitMov   (assembler.rdx, (sysint_t)0);
    assembler.emitIdiv  (assembler.rbx);
    assembler.emitRet   ();
    
    ResFunction f = assembler.make();
    
    printf ("%d\n", f());
    
    return 0;
}
