#include "Executor.h"
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <fstream>
#include <conio.h>

Executor::Executor (std::vector <ExecutableCommand*> &newCmds): execCmds (newCmds)
{
    executingCmd = 0;
    stack = new Stack;
    varData = new VariablesData;
    
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
         executeFunctions [i] = NULL;
    
    #define BIND_FUNCTION(a,b) executeFunctions [a] = b
    
    BIND_FUNCTION (Commands::PUSH,      &Executor::Push);
    BIND_FUNCTION (Commands::LABEL,     &Executor::Label);
    BIND_FUNCTION (Commands::JUMP,      &Executor::Jmp);
    BIND_FUNCTION (Commands::JB,        &Executor::Jb);
    BIND_FUNCTION (Commands::JA,        &Executor::Ja);
    BIND_FUNCTION (Commands::JBE,       &Executor::Jbe);
    BIND_FUNCTION (Commands::JAE,       &Executor::Jae);
    BIND_FUNCTION (Commands::JNE,       &Executor::Jne);
    BIND_FUNCTION (Commands::JE,        &Executor::Je);
    BIND_FUNCTION (Commands::CALL,      &Executor::Call);
    BIND_FUNCTION (Commands::ADD,       &Executor::Add);
    BIND_FUNCTION (Commands::SUB,       &Executor::Sub);
    BIND_FUNCTION (Commands::MUL,       &Executor::Mul);
    BIND_FUNCTION (Commands::DIV,       &Executor::Div);
    BIND_FUNCTION (Commands::TOP,       &Executor::Top);
    BIND_FUNCTION (Commands::DUP,       &Executor::Dup);
    BIND_FUNCTION (Commands::HELP,      &Executor::Help);
    BIND_FUNCTION (Commands::CLEAR,     &Executor::Clear);
    BIND_FUNCTION (Commands::CLS,       &Executor::Cls);
    BIND_FUNCTION (Commands::POP,       &Executor::Pop);
    BIND_FUNCTION (Commands::GETCH,     &Executor::Getch);
    BIND_FUNCTION (Commands::DECL,      &Executor::Decl);
    BIND_FUNCTION (Commands::POPTO,     &Executor::Popto);
    BIND_FUNCTION (Commands::PUSHFROM,  &Executor::Pushfrom);
    BIND_FUNCTION (Commands::MOREEQUAL, &Executor::Moreequal);
    BIND_FUNCTION (Commands::LESSEQUAL, &Executor::Lessequal);
    BIND_FUNCTION (Commands::MORE,      &Executor::More);
    BIND_FUNCTION (Commands::LESS,      &Executor::Less);
    BIND_FUNCTION (Commands::EQUAL,     &Executor::Equal);
    BIND_FUNCTION (Commands::RET,       &Executor::Ret);
}

bool Executor::Push ()
{
    int newDataToPushToStack = execCmds[executingCmd] -> intArgs[0];
    stack -> Push (newDataToPushToStack);
}

bool Executor::Label ()
{
    // Nothing to do. Label place will be found during JMP command execution
}

bool Executor::Jmp ()
{
    JumpCommands ();
}

bool Executor::Jb ()
{
    JumpCommands ();
}

bool Executor::Ja ()
{
    JumpCommands ();
}

bool Executor::Jae ()
{
    JumpCommands ();
}

bool Executor::Jbe ()
{
    JumpCommands ();
}

bool Executor::Je ()
{
    JumpCommands ();
}

bool Executor::Jne ()
{
    JumpCommands ();
}

bool Executor::Call ()
{
    JumpCommands ();
}

bool Executor::JumpCommands ()
{
    if ((execCmds [executingCmd] -> cmdNumber == Commands::JUMP) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JB) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JA) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JBE) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JAE) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JE) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::JNE) ||
        (execCmds [executingCmd] -> cmdNumber == Commands::CALL))
    {
        int numberOfJMPCmd = execCmds [executingCmd] -> cmdNumber;
        
        int placeOfLabelToJump = -1;
        
        // Find command LABEL in execution list on which we have to jump
        
        for (int i = 0; i < execCmds.size(); i++)
                if (execCmds [i] -> cmdNumber == Commands::LABEL &&
                    !strcmp (execCmds[i] -> stringArgs[0], execCmds[i] -> stringArgs[0]))
                    placeOfLabelToJump = i;
        
        // If command LABEL was not found - Error!     
                
        if (placeOfLabelToJump == -1) 
        {
                char str[100] = "";
                sprintf (str, "Label %s was not found", execCmds[executingCmd] -> stringArgs[0]);
                printf ("\nExecution error:\n======>>>>>> %s <<<<<<======", str);
                return false;
        }    
        
        bool necessityOfJump = false;
        
        if (numberOfJMPCmd == Commands::JUMP) necessityOfJump = true;
        else
        if (numberOfJMPCmd == Commands::CALL)
        {
            necessityOfJump = true;
            retStack.Push (executingCmd);
        }
        else
        {
            int last = stack -> Pop ();
            int penultimate = stack -> Pop ();
            
            if (numberOfJMPCmd == Commands::JB  && (last >  penultimate)) necessityOfJump = true;  
            if (numberOfJMPCmd == Commands::JA  && (last <  penultimate)) necessityOfJump = true;
            if (numberOfJMPCmd == Commands::JBE && (last >= penultimate)) necessityOfJump = true;
            if (numberOfJMPCmd == Commands::JAE && (last <= penultimate)) necessityOfJump = true;
            if (numberOfJMPCmd == Commands::JE  && (last == penultimate)) necessityOfJump = true;
            if (numberOfJMPCmd == Commands::JNE && (last != penultimate)) necessityOfJump = true;
                        
            stack -> Push (penultimate);
            stack -> Push (last);
        }
            
        if (necessityOfJump) executingCmd = placeOfLabelToJump;   
    }
}  

bool Executor::Dump ()
{
    stack -> Dump ();
} 

bool Executor::Add ()
{
    stack -> Push (stack->Pop() + stack->Pop());
} 

bool Executor::Sub ()
{
    stack -> Push (stack->Pop() - stack->Pop());
} 

bool Executor::Mul ()
{
    stack -> Push (stack->Pop() * stack->Pop());
} 

bool Executor::Div ()
{
    stack -> Push (stack->Pop() / stack->Pop());
} 

bool Executor::Top ()
{
    printf ("%d\n", stack->Top());
} 

bool Executor::Dup ()
{
    stack -> Push (stack->Top());
} 

bool Executor::Help ()
{
    printf ("Help unavalible\n");
} 

bool Executor::Clear ()
{
    stack -> data.clear();
}

bool Executor::Cls ()
{
    for (int i = 0; i < 100; i++) printf ("\n");
}

bool Executor::Pop ()
{
    stack -> Pop ();
}

bool Executor::Getch ()
{
    getch();
}

bool Executor::Decl ()
{
    /* Nothing to do because of all variables were pre-declared during execution
        independently of their places */
}

bool Executor::Popto ()
{
    Variable* assigningVariable = varData -> FindVar (execCmds[executingCmd] -> stringArgs[0]);
    assigningVariable -> value  = stack -> Pop(); 
} 

bool Executor::Pushfrom ()
{
    Variable* assigningVariable = varData -> FindVar (execCmds[executingCmd] -> stringArgs[0]);
    stack -> Push (assigningVariable -> value);
} 

bool Executor::Moreequal ()
{
    ComparisonCommands ();
} 

bool Executor::Lessequal ()
{
    ComparisonCommands ();
} 

bool Executor::More ()
{
    ComparisonCommands ();
} 

bool Executor::Less ()
{
    ComparisonCommands ();
} 

bool Executor::Equal ()
{
    ComparisonCommands ();
} 

bool Executor::ComparisonCommands ()
{
    int last = stack -> Pop ();
    int penultimate = stack -> Pop ();
    
    int operationResult = 0;
    
    if ((execCmds [executingCmd] -> cmdNumber == Commands::MOREEQUAL) && penultimate >= last) operationResult = 1;
    else
    if ((execCmds [executingCmd] -> cmdNumber == Commands::LESSEQUAL) && penultimate <= last) operationResult = 1;    
    else
    if ((execCmds [executingCmd] -> cmdNumber == Commands::MORE)      && penultimate > last)  operationResult = 1;    
    else
    if ((execCmds [executingCmd] -> cmdNumber == Commands::LESS)      && penultimate < last)  operationResult = 1;
    else
    if ((execCmds [executingCmd] -> cmdNumber == Commands::EQUAL)     && penultimate == last) operationResult = 1;    
                    
    stack -> Push (operationResult);    
} 

bool Executor::Ret ()
{
    executingCmd = retStack.Pop();
} 

bool Executor::DeclareAllVariables ()
{
    for (int i = 0; i < execCmds.size(); i++)
    {
        if (execCmds [i] -> cmdNumber == Commands::DECL)
        {
            Variable newVar;
            newVar.name = execCmds[i] -> stringArgs [0];
            
            varData -> PushVar (newVar);
        }
    }
}

void Executor::Execute()
{
    using namespace Commands;
    
    printf ("\nTranslating completed.\n"
            "Starting to execute. Output:\n");
    
    // Declare all variables independently of their places in code. I think it's convenient
    
    DeclareAllVariables ();
    
    while (executingCmd < execCmds.size())
    {
        if (executeFunctions [execCmds [executingCmd] -> cmdNumber] != NULL)    
            (this ->* executeFunctions [execCmds [executingCmd] -> cmdNumber]) ();
        else
        {
            char errData [256];
            sprintf (errData, "Unknown command. Command code - %d.", execCmds [executingCmd] -> cmdNumber);
            printf ("\nExecution error:\n======>>>>>>%s<<<<<<======", errData);
            return;
        }
        executingCmd++;
    }    
    executingCmd = 0;
}