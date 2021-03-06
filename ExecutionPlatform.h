#include "commands.h"
#include "ExecutableCommand.h"

#ifndef H_EXECUTION_PLATFORM
#define H_EXECUTION_PLATFORM

class ExecutionPlatform;

typedef int (*resultFunction)();
typedef bool (ExecutionPlatform::*executeFunction) ();

class ExecutionPlatform
{
protected:
    std::vector <ExecutableCommand*> execCmds;
    int executingCmd;
    
    executeFunction executeFunctions [MAX_CMDS_DECLS_ALLOW];
    
public:  
                 ExecutionPlatform ();
    virtual     ~ExecutionPlatform ();
         
    virtual resultFunction Execute             () = 0;
    virtual void           InitCmdsList        (std::vector <ExecutableCommand*> newCmds);
    
    virtual bool Push                () = 0;
    virtual bool Label               () = 0;
    virtual bool Jmp                 () = 0;
    virtual bool Jb                  () = 0;
    virtual bool Ja                  () = 0;
    virtual bool Jae                 () = 0;
    virtual bool Jbe                 () = 0;
    virtual bool Je                  () = 0;
    virtual bool Jne                 () = 0;
    virtual bool Call                () = 0;
    virtual bool Dump                () = 0;
    virtual bool Add                 () = 0;
    virtual bool Sub                 () = 0;
    virtual bool Mul                 () = 0;
    virtual bool Div                 () = 0;
    virtual bool Top                 () = 0;
    virtual bool Dup                 () = 0;
    virtual bool Clear               () = 0;
    virtual bool Cls                 () = 0;
    virtual bool Pop                 () = 0;
    virtual bool Getch               () = 0;
    virtual bool Decl                () = 0;
    virtual bool Popto               () = 0;
    virtual bool Pushfrom            () = 0;
    virtual bool Moreequal           () = 0;
    virtual bool Lessequal           () = 0;
    virtual bool More                () = 0; 
    virtual bool Less                () = 0;
    virtual bool Equal               () = 0;
    virtual bool NotEqual            () = 0;
    virtual bool Ret                 () = 0;
    virtual bool Print               () = 0;
    virtual bool NewLine             () = 0;
    virtual bool NewWord             () = 0;
    virtual bool PushPtr             () = 0;
    virtual bool PopPtr              () = 0;
};

#endif