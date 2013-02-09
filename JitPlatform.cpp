#include "JitPlatform.h"

JitPlatform::JitPlatform():
    rax (AsmJit::rax),
    rbx (AsmJit::rbx),
    rsp (AsmJit::rsp),
    nbp (AsmJit::nbp),
    rsi (AsmJit::rsi),
    rdi (AsmJit::rdi),
    nsp (AsmJit::nsp),
    nax (AsmJit::nax)    
{
    compiler = new AsmJit::Assembler;     
}

void JitPlatform::add (const reg& dst, const reg& src)
{
    compiler -> add (dst, src);
}

void JitPlatform::sub(const reg& dst, const reg& src)
{
    compiler -> sub (dst, src);
}

void JitPlatform::imul(const reg& dst)
{
    compiler -> imul (dst);
}

void JitPlatform::idiv(const reg& dst)
{
    compiler -> idiv (dst);
}

label JitPlatform::newLabel()
{
    return compiler -> newLabel ();
}

void JitPlatform::bind(const label& dst)
{
    compiler -> bind (dst);
}

void JitPlatform::call(void *dst)
{
    compiler -> call (dst);
}

void JitPlatform::call(const label& dst)
{
    compiler -> call (dst);
}

void JitPlatform::ret()
{
    compiler -> ret ();
}

void JitPlatform::cdqe()
{
    compiler -> cdqe ();
}

void JitPlatform::jmp(const label& dst)
{
    compiler -> jmp (dst);
}

void JitPlatform::je(const label& dst)
{
    compiler -> je (dst);
}

void JitPlatform::jne(const label& dst)
{
    compiler -> jne (dst);
}

void JitPlatform::ja(const label& dst)
{
    compiler -> ja (dst);
}

void JitPlatform::jae(const label& dst)
{
    compiler -> jae (dst);
}

void JitPlatform::jb(const label& dst)
{
    compiler -> jb (dst);
}

void JitPlatform::jbe(const label& dst)
{
    compiler -> jbe (dst);
}

void JitPlatform::mov(const reg& dst, const reg& src)
{
    compiler -> mov (dst, src);
}

void JitPlatform::mov(const reg& dst, sysint_t src)
{
    compiler -> mov (dst, src);
}

void JitPlatform::mov(const reg& dst, sysuint_t src)
{
    compiler -> mov (dst, src);
}

void JitPlatform::mov(const reg& dst, const int src)
{
    compiler -> mov (dst, src);
}

void JitPlatform::push(const sysint_t& src)
{
    compiler -> push (src);
}

void JitPlatform::push(const reg& src)
{
    compiler -> push (src);
}

void JitPlatform::pop(const reg& src)
{
    compiler -> pop (src);
}

void JitPlatform::cmp(const reg& dst, const reg& src)
{
    compiler -> cmp (dst, src); 
}

void JitPlatform::sete(const reg& dst)
{
    compiler -> sete (dst);
}

void JitPlatform::setne(const reg& dst)
{
    compiler -> setne (dst);
}

void JitPlatform::setg(const reg& dst)
{
    compiler -> setg (dst);
}

void JitPlatform::setge(const reg& dst)
{
    compiler -> setge (dst);
}

void JitPlatform::setl(const reg& dst)
{
    compiler -> setl (dst);
}

void JitPlatform::setle(const reg& dst)
{
    compiler -> setle (dst);
}
