#include "JitCompiler.h"
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <fstream>
#include <conio.h>

JitCompiler::JitCompiler (): ExecutionPlatform ()
{   
    compiler = new AsmJit::Assembler;
    
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
    BIND_FUNCTION (Commands::HELP,      &ExecutionPlatform::Help);
    BIND_FUNCTION (Commands::CLEAR,     &ExecutionPlatform::Clear);
    BIND_FUNCTION (Commands::CLS,       &ExecutionPlatform::Cls);
    BIND_FUNCTION (Commands::POP,       &ExecutionPlatform::Pop);
    BIND_FUNCTION (Commands::GETCH,     &ExecutionPlatform::Getch);
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
    
    #undef BIND_FUNCTION
}

JitCompiler::~JitCompiler()
{
}

static _cdecl int printWord (char* string)
{
    printf ("%s", string);
    return 0;
}

static _cdecl int printNumber (int number)
{
    printf ("%d", number);
    return 0;
}

bool JitCompiler::Push ()
{
    compiler -> push (execCmds[executingCmd] -> intArgs [0]);
}

bool JitCompiler::Label ()
{
    // Nothing to do. Label place will be found during JMP command execution
}

bool JitCompiler::Jmp ()
{
}

bool JitCompiler::Jb ()
{
}

bool JitCompiler::Ja ()
{
}

bool JitCompiler::Jae ()
{
}

bool JitCompiler::Jbe ()
{
}

bool JitCompiler::Je ()
{
}

bool JitCompiler::Jne ()
{
}

bool JitCompiler::Call ()
{
}

bool JitCompiler::JumpCommands ()
{
}  

bool JitCompiler::Dump ()
{
} 

bool JitCompiler::Add ()
{
    compiler -> pop  (AsmJit::eax);
    compiler -> pop  (AsmJit::ebx);
    compiler -> add  (AsmJit::eax, AsmJit::ebx);
    compiler -> push (AsmJit::eax);
} 

bool JitCompiler::Sub ()
{
    compiler -> pop  (AsmJit::eax);
    compiler -> pop  (AsmJit::ebx);
    compiler -> sub  (AsmJit::eax, AsmJit::ebx);
    compiler -> push (AsmJit::eax);    
} 

bool JitCompiler::Mul ()
{
    compiler -> pop  (AsmJit::eax);
    compiler -> pop  (AsmJit::ebx);
    compiler -> mul  (AsmJit::ebx);
    compiler -> push (AsmJit::eax);
} 

bool JitCompiler::Div ()
{
    compiler -> pop  (AsmJit::eax);
    compiler -> pop  (AsmJit::edx);
   // compiler -> div  (AsmJit::edx);
    compiler -> push (AsmJit::edx);    
} 

bool JitCompiler::Top ()
{
    compiler -> call ((void*)printNumber);    
} 

bool JitCompiler::Dup ()
{
} 

bool JitCompiler::Help ()
{
} 

bool JitCompiler::Clear ()
{
}

bool JitCompiler::Cls ()
{
}

bool JitCompiler::Pop ()
{
}

bool JitCompiler::Getch ()
{
}

bool JitCompiler::Decl ()
{
    /* Nothing to do because of all variables were pre-declared during execution
        independently of their places */
}

bool JitCompiler::Popto ()
{ 
} 

bool JitCompiler::Pushfrom ()
{
} 

bool JitCompiler::Moreequal ()
{
} 

bool JitCompiler::Lessequal ()
{
} 

bool JitCompiler::More ()
{
} 

bool JitCompiler::Less ()
{
} 

bool JitCompiler::Equal ()
{
} 

bool JitCompiler::NotEqual()
{
}

bool JitCompiler::ComparisonCommands ()
{ 
} 

bool JitCompiler::Ret ()
{
} 

bool JitCompiler::DeclareAllVariables ()
{
}

bool JitCompiler::Print()
{
     compiler -> push (reinterpret_cast <sysuint_t> (execCmds [executingCmd] -> stringArgs [0]));
     compiler -> call ((void*)printWord); 
     compiler -> pop (AsmJit::eax);
}

bool JitCompiler::NewLine()
{   
     compiler -> push (reinterpret_cast <sysuint_t> ("\n"));
     compiler -> call ((void*)printWord); 
     compiler -> pop (AsmJit::eax);
}

bool JitCompiler::NewWord()
{
     compiler -> push (reinterpret_cast <sysuint_t> (" "));
     compiler -> call ((void*)printWord); 
     compiler -> pop (AsmJit::eax);
}

resultFunction JitCompiler::Execute()
{
    using namespace Commands;
    using namespace AsmJit;
   
//     compiler -> newFunction(CALL_CONV_DEFAULT, FunctionBuilder1 <int, int>());
    
    // Declare all variables independently of their places in code. I think it's convenient
    
    DeclareAllVariables ();
    
    while (executingCmd < execCmds.size())
    {
        if (executeFunctions [execCmds [executingCmd] -> cmdNumber] != NULL)    
            (this ->* executeFunctions [execCmds [executingCmd] -> cmdNumber]) ();
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
    
    compiler -> mov(nax, 0);

    compiler -> mov(nsp, nbp);
    compiler -> pop(nbp);

    compiler -> ret();
    
    return function_cast <resultFunction> (compiler -> make ());
}