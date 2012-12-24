#include "codeblock.h"
#include <string.h>
#include <stdio.h>

#define DEBUG

#ifdef DEBUG
    #define $ if(true)
#else
    #define $ if(false)
#endif

CodeBlock::CodeBlock()
{
    currentCmdAmount = 0;
}

CodeBlock& CodeBlock::LoadBlock(const char* fileName)
{
    FILE* inF = fopen (fileName, "r");
    bool need = false;
    
    $ printf ("\n"
              "Starting to read out block of code\n\n");
    
    while (!feof (inF))
    {
          char string [256];
          int x = fscanf (inF, "%s", &string);
          if(x <= 0) break;
          
          if (!strcmp (string, "push"))
          {
                int number = 0;
                fscanf (inF, "%d", &number);  
                $ printf ("push %d\n", number);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::PUSH);
                execCmds [currentCmdAmount] -> addIntArg (number);
                currentCmdAmount++;
                
                continue;    
          }  
                             
          if (!strcmp (string, "add"))
          {  
                $ printf ("add\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::ADD);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "mul"))
          {  
                $ printf ("mul\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::MUL);
                currentCmdAmount++;
                
                continue;    
          }  
            
          if (!strcmp (string, "sub"))
          {  
                $ printf ("sub\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::SUB);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "dup"))
          {  
                $ printf ("dup\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::DUP);
                currentCmdAmount++;
                
                continue;    
          } 
          if (!strcmp (string, "dump"))
          {  
                $ printf ("dump\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::DUMP);
                currentCmdAmount++;
                
                continue;    
          }  
                   
          if (!strcmp (string, "top"))
          {  
                $ printf ("top\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::TOP);
                currentCmdAmount++;
                
                continue;    
          }           
          
          if (!strcmp (string, "pop"))
          {  
                $ printf ("pop\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::POP);
                currentCmdAmount++;
                
                continue;    
          }            
          
          if (!strcmp (string, "getch"))
          {  
                $ printf ("getch\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::GETCH);
                currentCmdAmount++;
                
                continue;    
          }
                     
          if (!strcmp (string, "clear"))
          {  
                $ printf ("clear\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::CLEAR);
                currentCmdAmount++;
                
                continue;    
          }            

          if (!strcmp (string, "cls"))
          {  
                $ printf ("cls\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::CLS);
                currentCmdAmount++;
                
                continue;    
          }  

          if (!strcmp (string, "help"))
          {  
                $ printf ("help\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::HELP);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "label") ||
              !strcmp (string, ":"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("label %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::LABEL);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "goto") ||
              !strcmp (string, "jump"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jump %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JUMP);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "jb"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jb %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JB);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "ja"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("ja %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JA);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jbe"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jbe %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JBE);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jae"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jae %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JAE);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "je"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("je %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JE);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jne"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jne %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::JNE);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "declare"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("declare %s\n", name);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::DECL);
                execCmds [currentCmdAmount] -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "popto"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("popto %s\n", name);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::POPTO);
                execCmds [currentCmdAmount] -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          }   
          
          if (!strcmp (string, "pushfrom"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("pushfrom %s\n", name);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::PUSHFROM);
                execCmds [currentCmdAmount] -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          }    
          
          if (!strcmp (string, ">="))
          { 
                $ printf (">=\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::MOREEQUAL);
                currentCmdAmount++;
                
                continue;    
          }
           
          if (!strcmp (string, "<="))
          { 
                $ printf ("<=\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::LESSEQUAL);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, ">"))
          { 
                $ printf (">\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::MORE);
                currentCmdAmount++;
                
                continue;    
          }

          if (!strcmp (string, "<"))
          { 
                $ printf ("<\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::LESS);
                currentCmdAmount++;
                
                continue;    
          }
   
          if (!strcmp (string, "=="))
          { 
                $ printf ("==\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::EQUAL);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "call"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("call %s\n", ch);
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::CALL);
                execCmds [currentCmdAmount] -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "div"))
          {  
                $ printf ("div\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::DIV);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "ret"))
          {  
                $ printf ("ret\n");
                
                execCmds [currentCmdAmount] = new ExecutableCommand (Commands::RET);
                currentCmdAmount++;
                
                continue;    
          }
    }
    
    $ printf ("\n");
    
    fclose (inF);
    return *this;
}

CodeBlock& CodeBlock::SetBlock (const char* string)
{
    FILE* fOut = fopen ("temp.txt", "w");
    fprintf (fOut, "%s", string);
    fclose (fOut);
    return LoadBlock ("temp.txt");
}

void CodeBlock::PrepareInformationToExecutor()
{
    $ printf ("Commands Amount - %d\n\n"
              "Starting to translate code into executor language\n\n", currentCmdAmount);
    
    FILE* fOut = fopen ("temp.txt", "w");
    
    for (int i = 0; i < currentCmdAmount; i++)
    {
        execCmds [i] -> printExecuteInformation (fOut);
    }
    
    $ printf ("\n");
    fclose  (fOut);
}

Executor& CodeBlock::InitExecutor()
{
    PrepareInformationToExecutor ();
    FILE* fIn = fopen ("temp.txt", "r");
    executor = new Executor (fIn);
    fclose (fIn);
    return *executor;
}
