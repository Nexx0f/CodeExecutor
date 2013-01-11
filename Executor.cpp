#include "Executor.h"
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <fstream>
#include <conio.h>

Executor::Executor (std::vector <ExecutableCommand*> &newCmds): execCmds (newCmds)
{
    dataSize = 0;
    stack = new Stack;
    varData = new VariablesData;
}

void Executor::Execute()
{
    using namespace Commands;
    
    printf ("\nTranslating completed.\n"
            "Starting to execute. Output:\n", dataSize);
    
    // Declare all variables independently of their places in code. I think it's convenient
    
    for (int i = 0; i < execCmds.size(); i++)
    {
        if (execCmds [i] -> cmdNumber == DECL)
        {
            Variable newVar;
            newVar.name = execCmds[i] -> stringArgs [0];
            
            varData -> PushVar (newVar);
        }
    }
    
    
    for (int executingCmd = 0; executingCmd < execCmds.size(); executingCmd++)
    {
        if (execCmds [executingCmd] -> cmdNumber == PUSH)
        {
            int newDataToPushToStack = execCmds[executingCmd] -> intArgs[0];
            stack -> Push (newDataToPushToStack);
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == LABEL)
        {
            // Nothing to do. Label place will be found during JMP command execution
        } 
        else
        if ((execCmds [executingCmd] -> cmdNumber == JUMP) ||
            (execCmds [executingCmd] -> cmdNumber == JB) ||
            (execCmds [executingCmd] -> cmdNumber == JA) ||
            (execCmds [executingCmd] -> cmdNumber == JBE) ||
            (execCmds [executingCmd] -> cmdNumber == JAE) ||
            (execCmds [executingCmd] -> cmdNumber == JE) ||
            (execCmds [executingCmd] -> cmdNumber == JNE) ||
            (execCmds [executingCmd] -> cmdNumber == CALL))
        {
            int numberOfJMPCmd = execCmds [executingCmd] -> cmdNumber;
            
            int placeOfLabelToJump = -1;
            
            // Find command LABEL in execution list on which we have to jump
            
            for (int i = 0; i < execCmds.size(); i++)
                 if (execCmds [executingCmd] -> cmdNumber == LABEL &&
                     !strcmp (execCmds[executingCmd] -> stringArgs[0], execCmds[i] -> stringArgs[0]))
                     placeOfLabelToJump = i;
            
            // If command LABEL was not found - Error!     
                 
            if (placeOfLabelToJump == -1) 
            {
                    char str[100] = "";
                    sprintf (str, "Label %s was not found", execCmds[executingCmd] -> stringArgs[0]);
                    printf ("\nExecution error:\n======>>>>>> %s <<<<<<======", str);
                    return;
            }    
            
            bool necessityOfJump = false;
            
            if (numberOfJMPCmd == JUMP) necessityOfJump = true;
            else
            if (numberOfJMPCmd == CALL)
            {
                necessityOfJump = true;
                retStack.Push (executingCmd);
            }
            else
            {
                int last = stack -> Pop ();
                int penultimate = stack -> Pop ();
                
                if (numberOfJMPCmd == JB  && (last >  penultimate)) necessityOfJump = true;  
                if (numberOfJMPCmd == JA  && (last <  penultimate)) necessityOfJump = true;
                if (numberOfJMPCmd == JBE && (last >= penultimate)) necessityOfJump = true;
                if (numberOfJMPCmd == JAE && (last <= penultimate)) necessityOfJump = true;
                if (numberOfJMPCmd == JE  && (last == penultimate)) necessityOfJump = true;
                if (numberOfJMPCmd == JNE && (last != penultimate)) necessityOfJump = true;
                           
                stack -> Push (penultimate);
                stack -> Push (last);
            }
             
            if (necessityOfJump) executingCmd = placeOfLabelToJump;
        }               
        else              
        if (execCmds [executingCmd] -> cmdNumber == DUMP)
        {
            stack -> Dump ();
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == ADD)
        {
            stack -> Push (stack->Pop() + stack->Pop());
        }  
        else
        if (execCmds [executingCmd] -> cmdNumber == MUL)
        {
            stack -> Push (stack->Pop() * stack->Pop());
        }  
        else
        if (execCmds [executingCmd] -> cmdNumber == DIV)
        {
            stack -> Push (stack->Pop() / stack->Pop());
        }                     
        else
        if (execCmds [executingCmd] -> cmdNumber == SUB)
        {
            stack -> Push (stack->Pop() - stack->Pop());
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == TOP)
        {
            printf ("%d\n", stack->Top());
        } 
        else
        if (execCmds [executingCmd] -> cmdNumber == DUP)
        {
            stack -> Push (stack->Top());
        }             
        else
        if (execCmds [executingCmd] -> cmdNumber == HELP)
        {
            printf ("Help unavalible\n");
        } 
        else
        if (execCmds [executingCmd] -> cmdNumber == CLEAR)
        {
            stack -> data.clear();
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == CLS)
        {
            for (int i = 0; i < 100; i++) printf ("\n");
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == POP)
        {
            stack -> Pop ();
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == GETCH)
        {
            getch();
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == DECL)
        {
            /* Nothing to do because of all variables were pre-declared during execution
               independently of their places */
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == POPTO)
        {
            Variable* assigningVariable = varData -> FindVar (execCmds[executingCmd] -> stringArgs[0]);
            assigningVariable -> value  = stack -> Pop(); 
        }
        else
        if (execCmds [executingCmd] -> cmdNumber == PUSHFROM)
        {
            Variable* assigningVariable = varData -> FindVar (execCmds[executingCmd] -> stringArgs[0]);
            stack -> Push (assigningVariable -> value);
        }                
        else
        if ((execCmds [executingCmd] -> cmdNumber == MOREEQUAL) ||
            (execCmds [executingCmd] -> cmdNumber == LESSEQUAL) ||
            (execCmds [executingCmd] -> cmdNumber == MORE) ||
            (execCmds [executingCmd] -> cmdNumber == LESS) ||
            (execCmds [executingCmd] -> cmdNumber == EQUAL))
        {
            int last = stack -> Pop ();
            int penultimate = stack -> Pop ();
            
            int operationResult = 0;
            
            if ((execCmds [executingCmd] -> cmdNumber == MOREEQUAL) && penultimate >= last) operationResult = 1;
            else
            if ((execCmds [executingCmd] -> cmdNumber == LESSEQUAL) && penultimate <= last) operationResult = 1;    
            else
            if ((execCmds [executingCmd] -> cmdNumber == MORE)      && penultimate > last)  operationResult = 1;    
            else
            if ((execCmds [executingCmd] -> cmdNumber == LESS)      && penultimate < last)  operationResult = 1;
            else
            if ((execCmds [executingCmd] -> cmdNumber == EQUAL)     && penultimate == last) operationResult = 1;    
                           
            stack -> Push (operationResult);
        }   
        else
        if (execCmds [executingCmd] -> cmdNumber == RET)
        {
            executingCmd = retStack.Pop();        
        }                                         
        else
        {
            char errData [256];
            sprintf (errData, "Unknown command. Command code - %d.", execCmds [executingCmd] -> cmdNumber);
            printf ("\nExecution error:\n======>>>>>>%s<<<<<<======", errData);
            return;
        }
    }                  
}