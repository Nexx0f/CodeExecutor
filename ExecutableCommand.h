#include <stdio.h>
#include <vector>

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
         
    bool  addIntArg              (int newArg);
    bool  addStringArg           (const char* newArg);
    
    bool  printExecuteInformation (FILE* ouF);
};
 
