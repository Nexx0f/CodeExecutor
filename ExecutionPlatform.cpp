#include "ExecutionPlatform.h"

ExecutionPlatform::ExecutionPlatform()
{
    executingCmd = 0;
    
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
         executeFunctions [i] = NULL;
}

void ExecutionPlatform::InitCmdsList (std::vector< ExecutableCommand* > newCmds)
{
    execCmds = newCmds;
}