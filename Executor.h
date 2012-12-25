#include "executor-stack_variables.h"
#include <stdio.h>
#include "commands.h"

const int MAX_DATA_SIZE = 2000;

class Executor
{
private:
    VariablesData* varData;
    Stack*         stack;
    Stack         retStack;
    std::vector <const char*> stringArguments;
    char  data            [MAX_DATA_SIZE];
    int   dataSize;
    
public:  
         Executor ();
         Executor (FILE* inF);
    
    void loadFile (FILE* inF);
         
    void Execute  ();
};