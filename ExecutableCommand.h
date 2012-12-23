#include <stdio.h>

const int MAX_ARGS_AMOUNT = 5;

/*CodeBlock create list of executable
  commands after parsing input code.
  Data of objects of this class determines
  input programm.*/
class ExecutableCommand
{
public:
    int   cmdNumber;
    
    int   intArgs                [MAX_ARGS_AMOUNT];
    int   intArgsAmount;
    
    char* stringArgs             [MAX_ARGS_AMOUNT];
    int   stringArgsAmount;
    
          ExecutableCommand      (int newCmdNumber);
         
    bool  addIntArg              (int newArg);
    bool  addStringArg           (char* newArg);
    
    bool  printExecuteInformation (FILE* ouF);
};
 
