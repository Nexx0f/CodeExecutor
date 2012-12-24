#include <iostream>
#include "codeblock.h"


int main(int argc, char **argv) 
{
    CodeBlock a;
    a.LoadBlock ("/home/nexx0f/projects/win32/CodeExecutor/build/test.txt").InitExecutor().Execute();
    //  a.languageDeclaration.PrintCommandsList(); 
   //  LanguageDeclaration x;
  //  x.DeclareCommands ();
  //  x.PrintCommandsList();
    return 0;
}
