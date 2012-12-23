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
    intArgsAmount = 0;
    stringArgsAmount = 0;
}

bool ExecutableCommand::addIntArg (int newArg)
{
    if (intArgsAmount + 1 < MAX_ARGS_AMOUNT)
    {
        intArgs [intArgsAmount] = newArg;
        intArgsAmount++;
        return true;
    }
    else return false;
}

bool ExecutableCommand::addStringArg (char* newArg)
{
    if (stringArgsAmount + 1 < MAX_ARGS_AMOUNT)
    {
        stringArgs [stringArgsAmount] = new char [strlen (newArg) + 1];
        strcpy (stringArgs [stringArgsAmount], newArg);
        stringArgsAmount++;
        return true;
    }
    else return false;
}

bool ExecutableCommand::printExecuteInformation (FILE* ouF)
{
    fprintf  (ouF,  "%d", cmdNumber);
    $ printf ("%d", cmdNumber);
    
    for (int i = 0; i < intArgsAmount; i++)
    {
        fprintf  (ouF, " %d", intArgs [i]);
        $ printf (" %d", intArgs [i]);
    }
    
    for (int i = 0; i < stringArgsAmount; i++)
    {
        fprintf  (ouF, " %s", stringArgs [i]);
        $ printf (" %s", stringArgs [i]);
    }
    
    fprintf (ouF, "\n");
    $ printf ("\n");
}
