#include "ExecutableCommand.h"
#include "Executor.h"

/*In fact, main project class. It contains control of
  interpretation and execution of the code.*/
class CodeBlock
{
private:
    std::vector <ExecutableCommand*> execCmds;
    LanguageDeclaration languageDeclaration;
    int currentCmdAmount;
    Executor* executor;
    
public:
               CodeBlock ();
    CodeBlock& LoadBlock (const char* fileName);
    CodeBlock& SetBlock  (const char* string);
    
    void PrepareInformationToExecutor ();
    Executor& InitExecutor            ();
};
