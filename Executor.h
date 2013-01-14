#include "executor-stack_variables.h"
#include <stdio.h>
#include "ExecutionPlatform.h"

class Executor: public ExecutionPlatform
{
private:
    VariablesData* varData;
    Stack*         stack;
    Stack          retStack;
    
public:  
         Executor ();
         
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