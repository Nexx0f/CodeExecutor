#include "JitPlatform.h"

#define DEBUG_JIT_PLATFORM

#ifdef DEBUG_JIT_PLATFORM
    #define $ if(true)
#else
    #define $ if(false)
#endif

JitPlatform::JitPlatform():
    rax (AsmJit::rax),
    rbx (AsmJit::rbx),
    rsp (AsmJit::rsp),
    rsi (AsmJit::rsi),
    rdi (AsmJit::rdi),
    rbp (AsmJit::rbp)
{
    compiler = new AsmJit::Assembler;
    cmdsAmount = 0;
    
    #define ADD_REG_NAME(a,b) regNames [a.getRegCode()] = b
    
    ADD_REG_NAME (AsmJit::rax, "rax");
    ADD_REG_NAME (AsmJit::rbx, "rbx");
    ADD_REG_NAME (AsmJit::rsp, "rsp");
    ADD_REG_NAME (AsmJit::rsi, "rsi");
    ADD_REG_NAME (AsmJit::rdi, "rdi");
    ADD_REG_NAME (AsmJit::rbp, "rbp");
    
    #undef ADD_REG_NAME
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
    compiler -> add (dst, src);
    $ printf ("    add   %s, %s\n", findRegName(dst.getRegCode()), findRegName(src.getRegCode()));
}

void JitPlatform::sub(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> sub (dst, src);
    $ printf ("    sub   %s, %s\n", findRegName(dst.getRegCode()), findRegName(src.getRegCode()));
}

void JitPlatform::imul(const reg& dst)
{
    cmdsAmount++;
    compiler -> imul (dst);
    $ printf ("    imul  %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::idiv(const reg& dst)
{
    cmdsAmount++;
    compiler -> idiv (dst);
    $ printf ("    idiv  %s\n", findRegName(dst.getRegCode()));
}

label JitPlatform::newLabel()
{
    return compiler -> newLabel ();
}

void JitPlatform::bind(const label& dst)
{
    cmdsAmount++;
    compiler -> bind (dst);
    $ printf ("label%d:\n", dst.getId());
}

void JitPlatform::call(void* dst)
{
    cmdsAmount++;
    compiler -> call (dst);
    $ printf ("    call  %p\n", dst);
}

void JitPlatform::call(const label& dst)
{
    cmdsAmount++;
    compiler -> call (dst);
    $ printf ("    call  label%d\n", dst.getId());
}

void JitPlatform::ret()
{
    cmdsAmount++;
    compiler -> ret ();
    $ printf ("    ret\n");
}

void JitPlatform::cdqe()
{
    cmdsAmount++;
    compiler -> cdqe ();
    $ printf ("    cdqe");
}

void JitPlatform::jmp(const label& dst)
{
    cmdsAmount++;
    compiler -> jmp (dst);
    $ printf ("    jmp   label%d\n", dst.getId());
}

void JitPlatform::je(const label& dst)
{
    cmdsAmount++;
    compiler -> je (dst);
    $ printf ("    je    label%d\n", dst.getId());
}

void JitPlatform::jne(const label& dst)
{
    cmdsAmount++;
    compiler -> jne (dst);
    $ printf ("    jne   label%d\n", dst.getId());
}

void JitPlatform::ja(const label& dst)
{
    cmdsAmount++;
    compiler -> ja (dst);
    $ printf ("    ja    label%d\n", dst.getId());
}

void JitPlatform::jae(const label& dst)
{
    cmdsAmount++;
    compiler -> jae (dst);
    $ printf ("    jae   label%d\n", dst.getId());
}

void JitPlatform::jb(const label& dst)
{
    cmdsAmount++;
    compiler -> jb (dst);
    $ printf ("    jb    label%d\n", dst.getId());
}

void JitPlatform::jbe(const label& dst)
{
    cmdsAmount++;
    compiler -> jbe (dst);
    $ printf ("    jbe   label%d\n", dst.getId());
}

void JitPlatform::mov(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> mov (dst, src);
    $ printf ("    mov   %s, %s\n", findRegName(dst.getRegCode()), findRegName(src.getRegCode()));
}

void JitPlatform::mov(const reg& dst, sysint_t src)
{
    cmdsAmount++;
    compiler -> mov (dst, src);
    $ printf ("    mov   %s, %d\n", findRegName(dst.getRegCode()), src);
}

void JitPlatform::mov(const reg& dst, sysuint_t src)
{
    cmdsAmount++;
    compiler -> mov (dst, src);
    $ printf ("    mov   %s, %u\n", findRegName(dst.getRegCode()), src);
}

void JitPlatform::mov(const reg& dst, const int src)
{
    cmdsAmount++;
    compiler -> mov (dst, src);
    $ printf ("    mov   %s, %d\n", findRegName(dst.getRegCode()), src);
}

void JitPlatform::push(const sysint_t& src)
{
    cmdsAmount++;
    compiler -> push (src);
    $ printf ("    push  %d\n", src);
}

void JitPlatform::push(const reg& src)
{
    cmdsAmount++;
    compiler -> push (src);
    $ printf ("    push  %s\n", findRegName(src.getRegCode()));
}

void JitPlatform::pop(const reg& src)
{
    cmdsAmount++;
    compiler -> pop (src);
    $ printf ("    pop   %s\n", findRegName(src.getRegCode()));
}

void JitPlatform::cmp(const reg& dst, const reg& src)
{
    cmdsAmount++;
    compiler -> cmp (dst, src);
    $ printf ("    mov   %s, %s\n", findRegName(dst.getRegCode()), findRegName(src.getRegCode()));
}

void JitPlatform::sete(const reg& dst)
{
    cmdsAmount++;
    compiler -> sete (dst);
    $ printf ("    sete  %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::setne(const reg& dst)
{
    cmdsAmount++;
    compiler -> setne (dst);
    $ printf ("    setne %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::setg(const reg& dst)
{
    cmdsAmount++;
    compiler -> setg (dst);
    $ printf ("    setg  %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::setge(const reg& dst)
{
    cmdsAmount++;
    compiler -> setge (dst);
    $ printf ("    setge %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::setl(const reg& dst)
{
    cmdsAmount++;
    compiler -> setl (dst);
    $ printf ("    setl  %s\n", findRegName(dst.getRegCode()));
}

void JitPlatform::setle(const reg& dst)
{
    cmdsAmount++;
    compiler -> setle (dst);
    $ printf ("    setle %s\n", findRegName(dst.getRegCode()));
}