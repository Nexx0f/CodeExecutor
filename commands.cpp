#include "commands.h"
#include <string.h>
#include <stdio.h>
 
CommandDeclaration::CommandDeclaration()
{
    cmdName = NULL;
    intArgsAllow = 0;
    stringArgsAllow = 0;
}
 
CommandDeclaration::CommandDeclaration (const char* newName, int newIntArgsAllow, int newStringArgsAllow)
{
    cmdName = newName;
    
    intArgsAllow = newIntArgsAllow;
    stringArgsAllow = newStringArgsAllow;
}
 
CommandDeclaration::~CommandDeclaration()
{
} 
 
LanguageDeclaration::LanguageDeclaration()
{
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
         cmdDeclarations [i] = NULL;
}
 
LanguageDeclaration::~LanguageDeclaration()
{
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
         if (cmdDeclarations [i] != NULL)
             delete cmdDeclarations [i];
} 
 
void LanguageDeclaration::DeclareCommands ()
{
    #define DECLARE_COMMAND(a,b,c,d) cmdDeclarations [a] = new CommandDeclaration (b, c, d) 
    
    using namespace Commands;
    DECLARE_COMMAND (PUSH,      "push",     1, 0);
    DECLARE_COMMAND (LABEL,     "label",    0, 1);
    DECLARE_COMMAND (JUMP,      "jump",     0, 1);
    DECLARE_COMMAND (JB,        "jb",       0, 1);
    DECLARE_COMMAND (JA,        "ja",       0, 1);
    DECLARE_COMMAND (JBE,       "jbe",      0, 1);
    DECLARE_COMMAND (JAE,       "jae",      0, 1);
    DECLARE_COMMAND (JE,        "je",       0, 1);
    DECLARE_COMMAND (JNE,       "jne",      0, 1);
    DECLARE_COMMAND (DECL,      "declare",  0, 1);
    DECLARE_COMMAND (POPTO,     "popto",    0, 1);
    DECLARE_COMMAND (PUSHFROM,  "pushfrom", 0, 1);
    DECLARE_COMMAND (CALL,      "call",     0, 1);
    DECLARE_COMMAND (ADD,       "add",      0, 0);
    DECLARE_COMMAND (MUL,       "mul",      0, 0);
    DECLARE_COMMAND (SUB,       "sub",      0, 0);
    DECLARE_COMMAND (DUP,       "dup",      0, 0);
    DECLARE_COMMAND (DUMP,      "dump",     0, 0);
    DECLARE_COMMAND (POP,       "pop",      0, 0);
    DECLARE_COMMAND (TOP,       "top",      0, 0);
    DECLARE_COMMAND (GETCH,     "getch",    0, 0);
    DECLARE_COMMAND (MOREEQUAL, "me",       0, 0);
    DECLARE_COMMAND (LESSEQUAL, "le",       0, 0);
    DECLARE_COMMAND (MORE,      "m",        0, 0);
    DECLARE_COMMAND (LESS,      "l",        0, 0);
    DECLARE_COMMAND (EQUAL,     "e",        0, 0);
    DECLARE_COMMAND (NOTEQUAL,  "ne",       0, 0);
    DECLARE_COMMAND (DIV,       "div",      0, 0);
    DECLARE_COMMAND (RET,       "ret",      0, 0);
    DECLARE_COMMAND (CLEAR,     "clear",    0, 0);
    DECLARE_COMMAND (CLS,       "cls",      0, 0);
    DECLARE_COMMAND (HELP,      "help",     0, 0);
    DECLARE_COMMAND (PRINT,     "print",    0, 1);
    DECLARE_COMMAND (NEWLINE,   "nline",    0, 0);
    DECLARE_COMMAND (NEWWORD,   "nword",    0, 0);
    
    #undef DECLARE_COMMAND
}

void LanguageDeclaration::PrintCommandsList()
{
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
         if (cmdDeclarations [i] != NULL) printf ("Cmd number - %d; Name - \"%s\"; Args - %d, %d\n",
                                                          i,
                                                          cmdDeclarations [i] -> cmdName,
                                                          cmdDeclarations [i] -> intArgsAllow,
                                                          cmdDeclarations [i] -> stringArgsAllow);
}

int LanguageDeclaration::FindCommand (const char* name)
{
    for (int i = 0; i < MAX_CMDS_DECLS_ALLOW; i++)
        if (cmdDeclarations [i] != NULL) 
            if (!strcmp (cmdDeclarations [i] -> cmdName, name))
                return i;
    return -1;
}
