#include "ExecutableCommand.h"

const int MAX_CMD_AMOUNT = 1000;

/*In fact, main project class. It contains control of
  interpretation and execution of the code.*/
class CodeBlock
{
private:
    ExecutableCommand* execCmds [MAX_CMD_AMOUNT];
    int currentCmdAmount;
    
public:
               CodeBlock ();
    CodeBlock& LoadBlock (const char* fileName);
    CodeBlock& SetBlock  (const char* string);
};
