#include "AsmJit/AsmJit.h"
#include <map>

typedef AsmJit::GPReg reg;
typedef AsmJit::Label label;

class JitPlatform
{
public:
    AsmJit::Assembler* compiler;
            
    int cmdsAmount;
    
    const reg&  rax;
    const reg&  rbx;
    const reg&  rsp;
    const reg&  rsi;
    const reg&  rdi;
    const reg&  rbp;
    
    std::map <int, const char*> regNames;
    
          JitPlatform        ();
    const char* findRegName (int id);
          
    void  mov      (const reg& dst, const reg&     src);
    void  mov      (const reg& dst, const sysint_t src);
    void  mov      (const reg& dst, const sysuint_t src);
    void  mov      (const reg& dst, const int       src);
    
    void  push     (const sysint_t& src);
    void  push     (const reg& src);
    
    void  pop      (const reg& src);
    
    void  cmp      (const reg& dst, const reg& src);
    void  sete     (const reg& dst);
    void  setne    (const reg& dst);
    void  setg     (const reg& dst);
    void  setge    (const reg& dst);
    void  setl     (const reg& dst);
    void  setle    (const reg& dst);
    
    void  call     (void*  dst);
    void  call     (const label& dst);
    void  ret      ();
    
    void  add      (const reg& dst, const reg& src);
    void  sub      (const reg& dst, const reg& src);
    void  imul     (const reg& dst);
    void  idiv     (const reg& dst);
    
    void  cdqe     ();
    
    void  jmp      (const label& dst);
    void  je       (const label& dst);
    void  jne      (const label& dst);
    void  ja       (const label& dst);
    void  jae      (const label& dst);
    void  jb       (const label& dst);
    void  jbe      (const label& dst);
    
    label newLabel ();
    void  bind     (const label& dst);
};