#include <iostream>
#include "codeblock.h"


int main(int argc, char **argv) 
{
    CodeBlock a;
    resultFunction x = a.LoadBlock ("cmdsTest.txt").InitExecutor(new JitCompiler).Execute();
    x ();
 
    return 0;
}
