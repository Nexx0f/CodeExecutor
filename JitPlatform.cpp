#include "JitPlatform.h"

#define DEBUG_JIT_PLATFORM

#ifdef DEBUG_JIT_PLATFORM
    #define $ if(true)
#else
    #define $ if(false)
#endif

JitPlatform::JitPlatform()
{
    compiler = new CodeGeneratorBackend;
    cmdsAmount = 0;
    
    #define INIT_REG(a,b,c); {regNames [a] = b; c = a;}
    
    INIT_REG (compiler -> rax, "rax", rax);
    INIT_REG (compiler -> rbx, "rbx", rbx);
    INIT_REG (compiler -> rdx, "rdx", rdx);
    INIT_REG (compiler -> rsp, "rsp", rsp);
    INIT_REG (compiler -> rsi, "rsi", rsi);
    INIT_REG (compiler -> rdi, "rdi", rdi);
    INIT_REG (compiler -> rbp, "rbp", rbp);
    
    //ADD_REG_NAME (AsmJit::rax, "rax");
    //ADD_REG_NAME (AsmJit::rbx, "rbx");
    //ADD_REG_NAME (AsmJit::rsp, "rsp");
    //ADD_REG_NAME (AsmJit::rsi, "rsi");
    //ADD_REG_NAME (AsmJit::rdi, "rdi");
    //ADD_REG_NAME (AsmJit::rbp, "rbp");
    
    #undef INIT_REG
}

const char *JitPlatform::findRegName(int id)
{
    cmdsAmount++;
    std::map <int, const char*>::const_iterator regName = regNames.find (id);
    return regName -> second;
}

void JitPlatform::add (const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> emitAdd (dst, src);
    $ printf ("    add   %s, %s\n", findRegName(dst), findRegName(src));
}

void JitPlatform::sub(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> emitSub (dst, src);
    $ printf ("    sub   %s, %s\n", findRegName(dst), findRegName(src));
}

void JitPlatform::imul(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitImul (dst);
    $ printf ("    imul  %s\n", findRegName(dst));
}

void JitPlatform::idiv(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitIdiv (dst);
    $ printf ("    idiv  %s\n", findRegName(dst));
}

label JitPlatform::newLabel()
{
    return compiler -> newLabel ();
}

void JitPlatform::bind(const label& dst)
{
    cmdsAmount++;
    compiler -> bindLabel (dst);
    $ printf ("label%d:\n", dst.labelId);
}

void JitPlatform::call(void* dst)
{
    cmdsAmount++;
    compiler -> emitCall (dst);
    $ printf ("    call  %p\n", dst);
}

void JitPlatform::call(const label& dst)
{
    cmdsAmount++;
    compiler -> emitCall (dst);
    $ printf ("    call  label%d\n", dst.labelId);
}

void JitPlatform::ret()
{
    cmdsAmount++;
    compiler -> emitRet ();
    $ printf ("    ret\n");
}

void JitPlatform::cdqe()
{
    cmdsAmount++;
    compiler -> emitCdqe ();
    $ printf ("    cdqe");
}

void JitPlatform::jmp(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJmp (dst);
    $ printf ("    jmp   label%d\n", dst.labelId);
}

void JitPlatform::je(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJe (dst);
    $ printf ("    je    label%d\n", dst.labelId);
}

void JitPlatform::jne(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJne (dst);
    $ printf ("    jne   label%d\n", dst.labelId);
}

void JitPlatform::ja(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJa (dst);
    $ printf ("    ja    label%d\n", dst.labelId);
}

void JitPlatform::jae(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJae (dst);
    $ printf ("    jae   label%d\n", dst.labelId);
}

void JitPlatform::jb(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJb (dst);
    $ printf ("    jb    label%d\n", dst.labelId);
}

void JitPlatform::jbe(const label& dst)
{
    cmdsAmount++;
    compiler -> emitJbe (dst);
    $ printf ("    jbe   label%d\n", dst.labelId);
}

void JitPlatform::mov(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> emitMov (dst, src);
    $ printf ("    mov   %s, %s\n", findRegName(dst), findRegName(src));
}

void JitPlatform::mov(const reg& dst, sysint_t src)
{
    cmdsAmount++;
    compiler -> emitMov (dst, src);
    $ printf ("    mov   %s, %d\n", findRegName(dst), src);
}

void JitPlatform::mov(const reg& dst, sysuint_t src)
{
    cmdsAmount++;
    compiler -> emitMov (dst, src);
    $ printf ("    mov   %s, %u\n", findRegName(dst), src);
}

void JitPlatform::mov(const reg& dst, const int src)
{
    cmdsAmount++;
    compiler -> emitMov (dst, (sysint_t)src);
    $ printf ("    mov   %s, %d\n", findRegName(dst), src);
}

void JitPlatform::push(const sysint_t& src)
{
    cmdsAmount++;
    compiler -> emitPush (src);
    $ printf ("    push  %d\n", src);
}

void JitPlatform::push(const reg& src)
{
    cmdsAmount++;
    compiler -> emitPush (src);
    $ printf ("    push  %s\n", findRegName(src));
}

void JitPlatform::pop(const reg& src)
{
    cmdsAmount++;
    compiler -> emitPop (src);
    $ printf ("    pop   %s\n", findRegName(src));
}

void JitPlatform::cmp(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> emitCmp (dst, src);
    $ printf ("    mov   %s, %s\n", findRegName(dst), findRegName(src));
}

void JitPlatform::sete(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSete (dst);
    $ printf ("    sete  %s\n", findRegName(dst));
}

void JitPlatform::setne(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSetne (dst);
    $ printf ("    setne %s\n", findRegName(dst));
}

void JitPlatform::setg(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSetg (dst);
    $ printf ("    setg  %s\n", findRegName(dst));
}

void JitPlatform::setge(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSetge (dst);
    $ printf ("    setge %s\n", findRegName(dst));
}

void JitPlatform::setl(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSetl (dst);
    $ printf ("    setl  %s\n", findRegName(dst));
}

void JitPlatform::setle(const reg& dst)
{
    cmdsAmount++;
    compiler -> emitSetle (dst);
    $ printf ("    setle %s\n", findRegName(dst));
}