#include "executor-stack_variables.h"
#include <stdio.h>
#include "commands.h"
#include "ExecutableCommand.h"

const int MAX_DATA_SIZE = 2000;

class Executor
{
private:
    VariablesData* varData;
    std::vector <ExecutableCommand*> &execCmds;
    Stack*         stack;
    Stack         retStack;
    std::vector <const char*> stringArguments;
    char  data            [MAX_DATA_SIZE];
    int   dataSize;
    
public:  
         Executor (std::vector <ExecutableCommand*> &newCmds);
         
    void Execute  ();
};