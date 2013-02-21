#include <map>
#include <string>

#ifndef H_COMMANDS
#define H_COMMANDS

namespace Commands 
{
    const int PUSH        = 1; 
    const int LABEL       = 2;
    const int JUMP        = 3;
    const int JB          = 4;
    const int JA          = 5;
    const int JBE         = 6;
    const int JAE         = 7;
    const int JE          = 8;
    const int JNE         = 9;
    const int DECL        = 10;
    const int POPTO       = 11;
    const int PUSHFROM    = 12;
    const int CALL        = 13;
    const int ADD         = 14;
    const int MUL         = 15;
    const int SUB         = 16;
    const int DUP         = 17;
    const int DUMP        = 18;
    const int TOP         = 19;
    const int POP         = 20;
    const int GETCH       = 21;
    const int MOREEQUAL   = 22;
    const int LESSEQUAL   = 23;
    const int MORE        = 24;
    const int LESS        = 25;
    const int EQUAL       = 26;
    const int DIV         = 27;
    const int RET         = 28;
    const int NOTEQUAL    = 29;
    const int CLEAR       = 30;
    const int CLS         = 31;
    const int HELP        = 32;
    const int PRINT       = 33;
    const int NEWLINE     = 34;
    const int NEWWORD     = 35;
    const int PUSHPTR     = 36;
    const int POPPTR      = 37;
};


const int MAX_CMDS_DECLS_ALLOW = 1000;

struct CommandDeclaration
{
    int         cmdNumber;
    std::string cmdName;
    int         intArgsAllow;
    int         stringArgsAllow;
    
    CommandDeclaration ();
    CommandDeclaration (const char* newName, int newIntArgsAllow, int newStringArgsAllow, int newNumber);
   ~CommandDeclaration ();
};

class LanguageDeclaration
{
public:
    std::map <std::string, CommandDeclaration*> cmdDeclarations;
    
    LanguageDeclaration    ();
   ~LanguageDeclaration    (); 
    
    void                DeclareCommands   ();
    CommandDeclaration*  FindCommand       (std::string name);
    void                PrintCommandsList ();
};
#endif
