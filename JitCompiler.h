#include "ExecutionPlatform.h"

#include "AsmJit/AsmJit.h"

class JitCompiler: public ExecutionPlatform
{  
private:
    
    AsmJit::Assembler* compiler;
    
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
    bool JumpCommands          ();
    bool Dump                  ();
    bool Add                   ();
    bool Sub                   ();
    bool Mul                   ();
    bool Div                   ();
    bool Top                   ();
    bool Dup                   ();
    bool Help                  ();
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
    bool DeclareAllVariables   ();  
};