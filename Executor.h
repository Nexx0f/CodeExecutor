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
    Stack          retStack;
    std::vector <const char*> stringArguments;
    int executingCmd;
    
    
public:  
         Executor (std::vector <ExecutableCommand*> &newCmds);
         
    void Execute  ();
    
    bool Push                ();
    bool Label               ();
    bool Jmp                 ();
    bool Jb                  ();
    bool Ja                  ();
    bool Jae                 ();
    bool Jbe                 ();
    bool Je                  ();
    bool Jne                 ();
    bool Call                ();
    bool JumpCommands        ();
    bool Dump                ();
    bool Add                 ();
    bool Sub                 ();
    bool Mul                 ();
    bool Div                 ();
    bool Top                 ();
    bool Dup                 ();
    bool Help                ();
    bool Clear               ();
    bool Cls                 ();
    bool Pop                 ();
    bool Getch               ();
    bool Decl                ();
    bool Popto               ();
    bool Pushfrom            ();
    bool Moreequal           ();
    bool Lessequal           ();
    bool More                (); 
    bool Less                ();
    bool Equal               ();
    bool ComparisonCommands  ();
    bool Ret                 ();
    bool DeclareAllVariables ();  
};