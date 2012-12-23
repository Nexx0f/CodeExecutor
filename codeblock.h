#include "ExecutableCommand.h"

const int MAX_CMD_AMOUNT = 1000;

class CodeBlock
{
private:
    ExecutableCommand* execCmds [MAX_CMD_AMOUNT];
    int currentCmdAmount;
    
public:
               CodeBlock ();
    CodeBlock& LoadBlock (const char* fileName);
};
