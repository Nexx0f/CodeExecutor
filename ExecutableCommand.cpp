#include "ExecutableCommand.h"
#include <string.h>
#include <stdio.h>

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

