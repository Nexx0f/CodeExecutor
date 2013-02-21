#include <stdio.h>
#include <vector>

#ifndef H_EXECUTABLE_COMMAND
#define H_EXECUTABLE_COMMAND

/*CodeBlock create list of executable
  commands after parsing input code.
  Data of objects of this class determines
  input programm.*/
class ExecutableCommand
{
public:
    int   cmdNumber;
    
    std::vector <int>   intArgs;
    
    std::vector <const char*> stringArgs;
    
          ExecutableCommand      (int newCmdNumber);
         ~ExecutableCommand      ();
          
    bool  addIntArg              (int newArg);
    bool  addStringArg           (const char* newArg);
    
    bool  printExecuteInformation (FILE* ouF);
};
 
#endif