#include <iostream>
#include "codeblock.h"

int main(int argc, char **argv) 
{
    CodeBlock a;
    a.LoadBlock ("/home/nexx0f/projects/win32/CodeExecutor/build/test.txt").SetBlock("push 41\n"
                                                                                     "declare variable");
    return 0;
}
