#include <iostream>
#include "codeblock.h"


int main(int argc, char **argv) 
{
    CodeBlock a;
    resultFunction x = a.LoadBlock ("/home/nexx0f/projects/win32/CodeExecutor/build/cmdsTest.txt").InitExecutor(new JitCompiler).Execute();
    x ();
 
    return 0;
}
