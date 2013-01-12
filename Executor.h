#include "executor-stack_variables.h"
#include <stdio.h>
#include "commands.h"
#include "ExecutableCommand.h"

class Executor;

typedef bool (Executor::*executeFunction) ();

class Executor
{
private:
    std::vector <ExecutableCommand*> &execCmds;
    int executingCmd;
    
    executeFunction executeFunctions [MAX_CMDS_DECLS_ALLOW];
        
    VariablesData* varData;
    Stack*         stack;
    Stack          retStack;
    
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