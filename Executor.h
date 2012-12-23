#include "executor-stack_variables.h"
#include <stdio.h>

const int MAX_CMD_AMOUNT = 1000;

class Executor
{
private:
    VariablesData* varData;
    Stack*         stack;
    Stack         retStack;
    char* stringArguments [MAX_CMD_AMOUNT];
    char  data            [2*MAX_CMD_AMOUNT];
    int   dataSize;
    
public:  
         Executor ();
         Executor (FILE* inF);
    
    void loadFile (FILE* inF);
         
    void Execute  ();
};