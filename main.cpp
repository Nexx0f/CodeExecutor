#include <iostream>
#include "codeblock.h"


int main(int argc, char **argv) 
{
    CodeBlock* a = new CodeBlock;
    resultFunction x = a -> LoadBlock ("cmdsTest.txt").InitExecutor(new JitCompiler).Execute();
    x ();
    delete a;
    return 0;
}
