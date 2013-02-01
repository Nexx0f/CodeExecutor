#include "codeblock.h"
#include <string.h>
#include <stdio.h>

const int MAX_VARIABLE_NAME_LENGTH = 256;

#define DEBUG

#ifdef DEBUG
    #define $ if(true)
#else
    #define $ if(false)
#endif

CodeBlock::CodeBlock()
{
    currentCmdAmount = 0;
    languageDeclaration.DeclareCommands();
}

CodeBlock::~CodeBlock()
{  
    for (int i = 0; i < execCmds.size(); i++)
         delete execCmds [i];
    delete executionPlatform;
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
          
          std::string stringStd (string);
          
          CommandDeclaration* cmd = languageDeclaration.FindCommand (stringStd);
          
         // if (cmd == -1)
         // {
          //    printf ("\n\n==Error==>>>>>> Undeclared command - %d <<<<<<==Error==\n\n", string);
          //    break;
          //}
          
          $ printf ("%s", string);
          
          execCmds.push_back (new ExecutableCommand (cmd -> cmdNumber));
          
          for (int i = 0; i < cmd -> intArgsAllow; i++)
          {
              int arg = 0;
              fscanf (inF, "%d", &arg);
              
              $ printf (" %d", arg);
              
              execCmds [currentCmdAmount] -> addIntArg (arg);
          }
          
          for (int i = 0; i < cmd -> stringArgsAllow; i++)
          {
              char arg [MAX_VARIABLE_NAME_LENGTH]; 
              fscanf (inF, "%s", arg);
              
              $ printf (" %s", arg);
              
              execCmds [currentCmdAmount] -> addStringArg (arg);
          }
          
          $ printf ("\n");
          
          currentCmdAmount++;   
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

ExecutionPlatform& CodeBlock::InitExecutor(ExecutionPlatform* newExecutionPlatform)
{
    executionPlatform = newExecutionPlatform;
    executionPlatform -> InitCmdsList (execCmds);
    return *executionPlatform;
}
