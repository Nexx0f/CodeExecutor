#include <iostream>
#include "codeblock.h"
#include "CodeGeneratorBackend.h"
#include <sys/mman.h>
#include <vector>
#include <stdio.h>

int main(int argc, char **argv) 
{
    CodeBlock* a = new CodeBlock;
    resultFunction x = a -> LoadBlock ("factorial.txt").InitExecutor(new JitCompiler).Execute();
    printf ("\nFunction was created!\nJit compilated function's output:\n");
    x ();
    printf ("\nI quit from the generated function.\n");         
    
    //CodeGeneratorBackend assembler;

    //Label l1 = assembler.newLabel ();
    //Label l2 = assembler.newLabel ();
    
    //assembler.emitMov   (assembler.rax, (sysint_t)141);
    //assembler.emitCmp   (assembler.rax, assembler.rax);
    //assembler.emitJmp   (l2);
    //assembler.bindLabel (l1);
    //assembler.emitMov   (assembler.rax, (sysint_t)4100);
    //assembler.emitMov   (assembler.rbx, (sysint_t)-100);
    //assembler.emitMov   (assembler.rdx, (sysint_t)0);
    //assembler.emitIdiv  (assembler.rbx);
    //assembler.emitRet   ();
    //assembler.bindLabel (l2);
    //assembler.emitCall  (l1);
    //assembler.emitMov   (assembler.rdi, assembler.rax);
    //assembler.emitRet   ();
    
    //ResFunction f = assembler.make();
    
    //f();
    //printf ("%d\n", f());
    
    return 0;
}
