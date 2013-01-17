//#include "Executor.h"
#include "JitCompiler.h"

/*In fact, main project class. It contains control of
  interpretation and execution of the code.*/
class CodeBlock
{
private:
    std::vector <ExecutableCommand*> execCmds;
    LanguageDeclaration languageDeclaration;
    int currentCmdAmount;
    ExecutionPlatform* executionPlatform;
    
public:
               CodeBlock ();
              ~CodeBlock ();
              
    CodeBlock& LoadBlock (const char* fileName);
    CodeBlock& SetBlock  (const char* string);
    
    ExecutionPlatform& InitExecutor   (ExecutionPlatform* newExecutionPlatform);
};
