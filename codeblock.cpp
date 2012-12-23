#include "codeblock.h"
#include "commands.h"
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
    
    while (!feof (inF))
    {
          char string [256];
          int x = fscanf (inF, "%s", &string);
          if(x <= 0) break;
          
          ExecutableCommand* currCmd = execCmds [currentCmdAmount];
          
          if (!strcmp (string, "push"))
          {
                int number = 0;
                fscanf (inF, "%d", &number);  
                $ printf ("push %d\n", number);
                
                currCmd = new ExecutableCommand (Commands::PUSH);
                currCmd -> addIntArg (number);
                currentCmdAmount++;
                
                continue;    
          }  
                             
          if (!strcmp (string, "add"))
          {  
                $ printf ("add\n");
                
                currCmd = new ExecutableCommand (Commands::ADD);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "mul"))
          {  
                $ printf ("mul\n");
                
                currCmd = new ExecutableCommand (Commands::MUL);
                currentCmdAmount++;
                
                continue;    
          }  
            
          if (!strcmp (string, "sub"))
          {  
                $ printf ("sub\n");
                
                currCmd = new ExecutableCommand (Commands::SUB);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "dup"))
          {  
                $ printf ("dup\n");
                
                currCmd = new ExecutableCommand (Commands::DUP);
                currentCmdAmount++;
                
                continue;    
          } 
          if (!strcmp (string, "dump"))
          {  
                $ printf ("dump\n");
                
                currCmd = new ExecutableCommand (Commands::DUMP);
                currentCmdAmount++;
                
                continue;    
          }  
                   
          if (!strcmp (string, "top"))
          {  
                $ printf ("top\n");
                
                currCmd = new ExecutableCommand (Commands::TOP);
                currentCmdAmount++;
                
                continue;    
          }           
          
          if (!strcmp (string, "pop"))
          {  
                $ printf ("pop\n");
                
                currCmd = new ExecutableCommand (Commands::POP);
                currentCmdAmount++;
                
                continue;    
          }            
          
          if (!strcmp (string, "getch"))
          {  
                $ printf ("getch\n");
                
                currCmd = new ExecutableCommand (Commands::GETCH);
                currentCmdAmount++;
                
                continue;    
          }
                     
          if (!strcmp (string, "clear"))
          {  
                $ printf ("clear\n");
                
                currCmd = new ExecutableCommand (Commands::CLEAR);
                currentCmdAmount++;
                
                continue;    
          }            

          if (!strcmp (string, "cls"))
          {  
                $ printf ("cls\n");
                
                currCmd = new ExecutableCommand (Commands::CLS);
                currentCmdAmount++;
                
                continue;    
          }  

          if (!strcmp (string, "help"))
          {  
                $ printf ("help\n");
                
                currCmd = new ExecutableCommand (Commands::HELP);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "label") ||
              !strcmp (string, ":"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("label %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::LABEL);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "goto") ||
              !strcmp (string, "jump"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jump %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JUMP);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "jb"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jb %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JB);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "ja"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("ja %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JA);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jbe"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jbe %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JBE);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jae"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jae %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JAE);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "je"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("je %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JE);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, "jne"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("jne %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::JNE);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "declare"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("declare %s\n", name);
                
                currCmd = new ExecutableCommand (Commands::DECL);
                currCmd -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "popto"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("popto %s\n", name);
                
                currCmd = new ExecutableCommand (Commands::POPTO);
                currCmd -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          }   
          
          if (!strcmp (string, "pushfrom"))
          {
                char name [256] = "";      
                fscanf (inF, " %s", &name);  
                $ printf ("pushfrom %s\n", name);
                
                currCmd = new ExecutableCommand (Commands::PUSHFROM);
                currCmd -> addStringArg (name);
                currentCmdAmount++;
                
                continue;    
          }    
          
          if (!strcmp (string, ">="))
          { 
                $ printf (">=\n");
                
                currCmd = new ExecutableCommand (Commands::MOREEQUAL);
                currentCmdAmount++;
                
                continue;    
          }
           
          if (!strcmp (string, "<="))
          { 
                $ printf ("<=\n");
                
                currCmd = new ExecutableCommand (Commands::LESSEQUAL);
                currentCmdAmount++;
                
                continue;    
          }
          
          if (!strcmp (string, ">"))
          { 
                $ printf (">\n");
                
                currCmd = new ExecutableCommand (Commands::MORE);
                currentCmdAmount++;
                
                continue;    
          }

          if (!strcmp (string, "<"))
          { 
                $ printf ("<\n");
                
                currCmd = new ExecutableCommand (Commands::LESS);
                currentCmdAmount++;
                
                continue;    
          }
   
          if (!strcmp (string, "=="))
          { 
                $ printf ("==\n");
                
                currCmd = new ExecutableCommand (Commands::EQUAL);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "call"))
          {
                char ch[256] = "";
                fscanf (inF, " %s", &ch); 
                $ printf ("call %s\n", ch);
                
                currCmd = new ExecutableCommand (Commands::CALL);
                currCmd -> addStringArg (ch);
                currentCmdAmount++;
                
                continue;    
          } 
          
          if (!strcmp (string, "div"))
          {  
                $ printf ("div\n");
                
                currCmd = new ExecutableCommand (Commands::DIV);
                currentCmdAmount++;
                
                continue;    
          }  
          
          if (!strcmp (string, "ret"))
          {  
                $ printf ("ret\n");
                
                currCmd = new ExecutableCommand (Commands::RET);
                currentCmdAmount++;
                
                continue;    
          }
    }
}
