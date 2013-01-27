#include "ExecutableCommand.h"
#include <string.h>
#include <stdio.h>

#define DEBUG

#ifdef DEBUG
    #define $ if(true)
#else
    #define $ if(false)
#endif

ExecutableCommand::ExecutableCommand (int newCmdNumber)
{
    cmdNumber = newCmdNumber;
}

ExecutableCommand::~ExecutableCommand()
{
    for (int i = 0; i < stringArgs.size(); i++)
         delete stringArgs [i];
}

bool ExecutableCommand::addIntArg (int newArg)
{
    intArgs.push_back (newArg);
    return true;
}

bool ExecutableCommand::addStringArg (const char* newArg)
{
    char* arg = new char [strlen (newArg)];
    strcpy (arg, newArg);
    stringArgs.push_back (arg);
    return true;
}

bool ExecutableCommand::printExecuteInformation (FILE* ouF)
{
    fprintf  (ouF,  "%d", cmdNumber);
    $ printf ("%d", cmdNumber);
    
    for (int i = 0; i < intArgs.size(); i++)
    {
        fprintf  (ouF, " %d", intArgs [i]);
        $ printf (" %d", intArgs [i]);
    }
    
    for (int i = 0; i < stringArgs.size(); i++)
    {
        fprintf  (ouF, " %s", stringArgs [i]);
        $ printf (" %s", stringArgs [i]);
    }
    
    fprintf (ouF, "\n");
    $ printf ("\n");
}
