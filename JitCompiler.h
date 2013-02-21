#ifndef H_JITCOMPILER
#define H_JITCOMPILER

#include "ExecutionPlatform.h"
#include "executor-stack_variables.h"
#include <map>
#include <string>
#include "JitPlatform.h"

class JitCompiler: public ExecutionPlatform
{  
public:
    JitPlatform*                  compiler;
    std::map <std::string, label> labelsData;
    VariablesData*                varData;
    
public:  
         JitCompiler ();
        ~JitCompiler (); 
         
    resultFunction Execute     ();
    
    bool Push                  ();
    bool Label                 ();
    bool Jmp                   ();
    bool Jb                    ();
    bool Ja                    ();
    bool Jae                   ();
    bool Jbe                   ();
    bool Je                    ();
    bool Jne                   ();
    bool Call                  ();
    bool Dump                  ();
    bool Add                   ();
    bool Sub                   ();
    bool Mul                   ();
    bool Div                   ();
    bool Top                   ();
    bool Dup                   ();
    bool Clear                 ();
    bool Cls                   ();
    bool Pop                   ();
    bool Getch                 ();
    bool Decl                  ();
    bool Popto                 ();
    bool Pushfrom              ();
    bool Moreequal             ();
    bool Lessequal             ();
    bool More                  (); 
    bool Less                  ();
    bool Equal                 ();
    bool NotEqual              ();
    bool ComparisonCommands    ();
    bool Ret                   ();
    bool Print                 ();
    bool NewLine               ();
    bool NewWord               ();
    bool PushPtr               ();
    bool PopPtr                ();
    
    bool DeclareAllLabels      ();
    bool ProcessJumpCommands   ();
};

#endif