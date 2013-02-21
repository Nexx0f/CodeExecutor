#include "JitCompiler.h"
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <fstream>

#define DEBUG

#ifdef DEBUG
    #define $ if(true)
#else
    #define $ if(false)
#endif

VariablesData* variablesData;

JitCompiler::JitCompiler (): ExecutionPlatform ()
{   
    compiler = new JitPlatform;
    variablesData = new VariablesData;
    varData = variablesData;
    
    #define BIND_FUNCTION(a,b) executeFunctions [a] = b
    
    BIND_FUNCTION (Commands::PUSH,      &ExecutionPlatform::Push);
    BIND_FUNCTION (Commands::LABEL,     &ExecutionPlatform::Label);
    BIND_FUNCTION (Commands::JUMP,      &ExecutionPlatform::Jmp);
    BIND_FUNCTION (Commands::JB,        &ExecutionPlatform::Jb);
    BIND_FUNCTION (Commands::JA,        &ExecutionPlatform::Ja);
    BIND_FUNCTION (Commands::JBE,       &ExecutionPlatform::Jbe);
    BIND_FUNCTION (Commands::JAE,       &ExecutionPlatform::Jae);
    BIND_FUNCTION (Commands::JNE,       &ExecutionPlatform::Jne);
    BIND_FUNCTION (Commands::JE,        &ExecutionPlatform::Je);
    BIND_FUNCTION (Commands::CALL,      &ExecutionPlatform::Call);
    BIND_FUNCTION (Commands::ADD,       &ExecutionPlatform::Add);
    BIND_FUNCTION (Commands::SUB,       &ExecutionPlatform::Sub);
    BIND_FUNCTION (Commands::MUL,       &ExecutionPlatform::Mul);
    BIND_FUNCTION (Commands::DIV,       &ExecutionPlatform::Div);
    BIND_FUNCTION (Commands::TOP,       &ExecutionPlatform::Top);
    BIND_FUNCTION (Commands::DUP,       &ExecutionPlatform::Dup);
    //BIND_FUNCTION (Commands::CLEAR,     &ExecutionPlatform::Clear);
    //BIND_FUNCTION (Commands::CLS,       &ExecutionPlatform::Cls);
    BIND_FUNCTION (Commands::POP,       &ExecutionPlatform::Pop);
    //BIND_FUNCTION (Commands::GETCH,     &ExecutionPlatform::Getch);(more
    BIND_FUNCTION (Commands::DECL,      &ExecutionPlatform::Decl);
    BIND_FUNCTION (Commands::POPTO,     &ExecutionPlatform::Popto);
    BIND_FUNCTION (Commands::PUSHFROM,  &ExecutionPlatform::Pushfrom);
    BIND_FUNCTION (Commands::MOREEQUAL, &ExecutionPlatform::Moreequal);
    BIND_FUNCTION (Commands::LESSEQUAL, &ExecutionPlatform::Lessequal);
    BIND_FUNCTION (Commands::MORE,      &ExecutionPlatform::More);
    BIND_FUNCTION (Commands::LESS,      &ExecutionPlatform::Less);
    BIND_FUNCTION (Commands::NOTEQUAL,  &ExecutionPlatform::NotEqual);
    BIND_FUNCTION (Commands::EQUAL,     &ExecutionPlatform::Equal);
    BIND_FUNCTION (Commands::RET,       &ExecutionPlatform::Ret);
    BIND_FUNCTION (Commands::PRINT,     &ExecutionPlatform::Print);
    BIND_FUNCTION (Commands::NEWLINE,   &ExecutionPlatform::NewLine);
    BIND_FUNCTION (Commands::NEWWORD,   &ExecutionPlatform::NewWord);
    BIND_FUNCTION (Commands::PUSHPTR,   &ExecutionPlatform::PushPtr);
    BIND_FUNCTION (Commands::POPPTR,    &ExecutionPlatform::PopPtr);
    
    #undef BIND_FUNCTION
}

JitCompiler::~JitCompiler()
{
    delete compiler;
} 

static int printWord (char* string)
{
    printf ("%s", string);
    return 0;
}

static int printNumber (sysint_t* number)
{
    printf ("%d", *number);
    return 0;
}

static int addVariableToData (const char* name)
{
    Variable newVar = {name, 0};
    variablesData -> PushVar (newVar);
    return 0;
}

static int equateVariable (const char* name, int newValue)
{
    Variable* var = variablesData -> FindVar(name);
    var -> value = newValue;
    return 0;
}

static int returnValueOfVariable (const char* name)
{
    Variable* var = variablesData -> FindVar (name);
    return var -> value;
}

static sysint_t* returnPointerToVariable (const char* name)
{
    Variable* var = variablesData -> FindVar (name);
    return &(var -> value);    
}

static int pushValueToPointer (const char* name, sysint_t newValue)
{
    Variable* var = variablesData -> FindVar (name);
    *(reinterpret_cast <sysint_t*> (var -> value)) = newValue;
    return 0;
}

bool JitCompiler::Push ()
{
    compiler -> push (execCmds[executingCmd] -> intArgs [0]);
}

bool JitCompiler::Label ()
{
    std::string stringToFind (execCmds [executingCmd] -> stringArgs [0]);
    std::map <std::string, label>::const_iterator foundLabel = labelsData.find (stringToFind);
    compiler -> bind (foundLabel -> second);
}

bool JitCompiler::Jmp ()
{
    std::string stringToFind (execCmds [executingCmd] -> stringArgs [0]);
    std::map <std::string, label>::const_iterator foundLabel = labelsData.find (stringToFind);
    compiler -> jmp (foundLabel -> second);
}

bool JitCompiler::Jb ()
{
    ProcessJumpCommands ();
}       

bool JitCompiler::Ja ()
{
    ProcessJumpCommands ();
}

bool JitCompiler::Jae ()
{
    ProcessJumpCommands ();
}

bool JitCompiler::Jbe ()
{
    ProcessJumpCommands ();
}

bool JitCompiler::Je ()
{
    ProcessJumpCommands ();
}

bool JitCompiler::Jne ()
{
    ProcessJumpCommands ();
}

bool JitCompiler::Call ()
{
    std::string stringToFind (execCmds [executingCmd] -> stringArgs [0]);
    std::map <std::string, label>::const_iterator foundLabel = labelsData.find (stringToFind);
    compiler -> call (foundLabel -> second);
}

bool JitCompiler::ProcessJumpCommands ()
{
    std::string stringToFind (execCmds [executingCmd] -> stringArgs [0]);
    std::map <std::string, label>::const_iterator foundLabel = labelsData.find (stringToFind);
    
    compiler -> pop  (compiler -> rax);
    compiler -> pop  (compiler -> rbx);
    compiler -> cmp  (compiler -> rax, compiler -> rbx);
    compiler -> push (compiler -> rbx);
    compiler -> push (compiler -> rax);
    
    if (execCmds [executingCmd] -> cmdNumber == Commands::JE)  compiler -> je    (foundLabel -> second);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::JA)  compiler -> ja    (foundLabel -> second);
    else        
    if (execCmds [executingCmd] -> cmdNumber == Commands::JAE) compiler -> jae   (foundLabel -> second);
    else        
    if (execCmds [executingCmd] -> cmdNumber == Commands::JB)  compiler -> jb    (foundLabel -> second);
    else        
    if (execCmds [executingCmd] -> cmdNumber == Commands::JBE) compiler -> jbe   (foundLabel -> second);
    else        
    if (execCmds [executingCmd] -> cmdNumber == Commands::JNE) compiler -> jne   (foundLabel -> second);            
}  

bool JitCompiler::Dump ()
{
} 

bool JitCompiler::Add ()
{
    compiler -> pop  (compiler -> rax);
    compiler -> pop  (compiler -> rbx);
    compiler -> add  (compiler -> rax, compiler -> rbx);
    compiler -> push (compiler -> rax);
} 

bool JitCompiler::Sub ()
{
    compiler -> pop  (compiler -> rax);
    compiler -> pop  (compiler -> rbx);
    compiler -> sub  (compiler -> rax, compiler -> rbx);
    compiler -> push (compiler -> rax);    
} 

bool JitCompiler::Mul ()
{
    compiler -> pop   (compiler -> rax);
    compiler -> pop   (compiler -> rbx);
    compiler -> imul  (compiler -> rbx);
    compiler -> push  (compiler -> rax);
} 

bool JitCompiler::Div ()
{
     compiler -> pop   (compiler -> rax);
     compiler -> pop   (compiler -> rbx);
     compiler -> cdqe  ();
     compiler -> idiv  (compiler -> rbx);
     compiler -> push  (compiler -> rax);    
} 

bool JitCompiler::Top ()
{
    compiler -> mov  (compiler -> rdi, compiler -> rsp);
    compiler -> call ((void*)printNumber);    
} 

bool JitCompiler::Dup ()
{
    compiler -> pop  (compiler -> rax);
    compiler -> push (compiler -> rax);
    compiler -> push (compiler -> rax);
} 

bool JitCompiler::Clear ()
{
}

bool JitCompiler::Cls ()
{
}

bool JitCompiler::Pop ()
{
   compiler -> pop (compiler -> rbx);
}

bool JitCompiler::Getch ()
{
}

bool JitCompiler::Decl ()
{
    compiler -> mov (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> call ((void*)addVariableToData);
}

bool JitCompiler::Popto ()
{ 
    compiler -> mov  (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> pop  (compiler -> rsi);
    compiler -> call ((void*)equateVariable);
} 

bool JitCompiler::Pushfrom ()
{
    compiler -> mov  (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> call ((void*)returnValueOfVariable);
    compiler -> push (compiler -> rax);
} 

bool JitCompiler::Moreequal ()
{
    ComparisonCommands ();
} 

bool JitCompiler::Lessequal ()
{
    ComparisonCommands ();
} 

bool JitCompiler::More ()
{
    ComparisonCommands ();
} 

bool JitCompiler::Less ()
{
    ComparisonCommands ();
} 

bool JitCompiler::Equal ()
{
    ComparisonCommands ();
} 

bool JitCompiler::NotEqual()
{
    ComparisonCommands ();
}

bool JitCompiler::ComparisonCommands ()
{
    compiler -> pop  (compiler -> rax);
    compiler -> pop  (compiler -> rbx);
    compiler -> cmp  (compiler -> rax, compiler -> rbx);
    
    if (execCmds [executingCmd] -> cmdNumber == Commands::EQUAL)     compiler -> sete (compiler -> rax);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::NOTEQUAL)  compiler -> setne (compiler -> rax);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::MORE)      compiler -> setg (compiler -> rax);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::MOREEQUAL) compiler -> setge (compiler -> rax);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::LESS)      compiler -> setl (compiler -> rax);
    else
    if (execCmds [executingCmd] -> cmdNumber == Commands::LESSEQUAL) compiler -> setle (compiler -> rax);
    
    compiler -> push (compiler -> rax);
} 

bool JitCompiler::Ret ()
{
    compiler -> ret ();
} 

bool JitCompiler::PopPtr()
{
    compiler -> mov  (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> pop  (compiler -> rsi);
    compiler -> call ((void*)pushValueToPointer);
}

bool JitCompiler::PushPtr()
{
    compiler -> mov  (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> call ((void*)returnPointerToVariable);
    compiler -> push (compiler -> rax);
}

bool JitCompiler::Print()
{
    compiler -> mov (compiler -> rdi, reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
    compiler -> call ((void*)printWord); 
}

bool JitCompiler::NewLine()
{   
    compiler -> mov (compiler -> rdi, reinterpret_cast <sysuint_t> ("\n"));
    compiler -> call ((void*)printWord); 
}

bool JitCompiler::NewWord()
{
    compiler -> mov (compiler -> rdi, reinterpret_cast <sysuint_t> (" "));
    compiler -> call ((void*)printWord);
}

bool JitCompiler::DeclareAllLabels()
{
    for (int labelCmd = 0; labelCmd < execCmds.size(); labelCmd++)
        if (execCmds [labelCmd] -> cmdNumber == Commands::LABEL)
        {
            std::string newLabelName (execCmds [labelCmd] -> stringArgs [0]);
            labelsData [newLabelName] = compiler -> newLabel ();
        }

}

resultFunction JitCompiler::Execute()
{
    using namespace Commands;
    
    $ puts ("\nTranslated code:\n");
    
    compiler -> push (compiler -> rbp);
    compiler -> mov  (compiler -> rbp, compiler -> rsp);
    
    DeclareAllLabels (); 
     
    while (executingCmd < execCmds.size())
    {
        if (executeFunctions [execCmds [executingCmd] -> cmdNumber] != NULL)
        {
           (this ->* executeFunctions [execCmds [executingCmd] -> cmdNumber]) ();
        }
        else
        {
            char errData [256];
            sprintf (errData, "Unknown command. Command code - %d.", execCmds [executingCmd] -> cmdNumber);
            printf ("\nExecution error:\n======>>>>>>%s<<<<<<======", errData);
            return NULL;
        }
        executingCmd++;
    }    
    executingCmd = 0;
    
    compiler -> mov(compiler -> rax, 0);

    compiler -> mov(compiler -> rsp, compiler -> rbp);
    compiler -> pop(compiler -> rbp);

    compiler -> ret();
    
    printf ("\nAmount of commands and amount after translating ratio: %d/%d\n",
            execCmds.size(), compiler -> cmdsAmount);
    
    return AsmJit::function_cast <resultFunction> (compiler -> compiler -> make ());
}