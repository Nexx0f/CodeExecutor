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
    const int ADD         = 100;
    const int MUL         = 101;
    const int SUB         = 102;
    const int DUP         = 103;
    const int DUMP        = 104;
    const int TOP         = 105;
    const int POP         = 106;
    const int GETCH       = 107;
    const int MOREEQUAL   = 108;
    const int LESSEQUAL   = 109;
    const int MORE        = 110;
    const int LESS        = 111;
    const int EQUAL       = 112;
    const int DIV         = 113;
    const int RET         = 114;
    const int NOTEQUAL    = 115;
    const int CLEAR       = 200;
    const int CLS         = 201;
    const int HELP        = 202;
};


const int MAX_CMDS_DECLS_ALLOW = 1000;

struct CommandDeclaration
{
    const char* cmdName;
    int intArgsAllow;
    int stringArgsAllow;
    
    CommandDeclaration ();
    CommandDeclaration (const char* newName, int newIntArgsAllow, int newStringArgsAllow);
   ~CommandDeclaration ();
};

class LanguageDeclaration
{
public:
    CommandDeclaration* cmdDeclarations [MAX_CMDS_DECLS_ALLOW];
    
    LanguageDeclaration    ();
   ~LanguageDeclaration    (); 
    
    void DeclareCommands   ();
    int FindCommand        (const char* name);
    void PrintCommandsList ();
};

