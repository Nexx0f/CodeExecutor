#include <iostream>
#include "codeblock.h"


int main(int argc, char **argv) 
{
    CodeBlock* a = new CodeBlock;
    resultFunction x = a -> LoadBlock ("cmdsTest.txt").InitExecutor(new Executor).Execute();
    //printf ("\nFunction was created!\nJit compilated function's output:\n");
    //x ();
    //printf ("\nI quit from the generated function.\n");         
    
    return 0;
}
