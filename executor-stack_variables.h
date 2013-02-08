#ifndef H_EXECUTOR-STACK_VARIABLES
#define H_EXECUTOR-STACK_VARIABLES

#include <vector>
#include "AsmJit/AsmJit.h"

struct Variable
{
    const char* name;
    sysint_t value;   
};

class VariablesData
{
public:
    std::vector <Variable> data;
    int                    currAmountVar;
     
public:    
              VariablesData   ();    
             ~VariablesData   (); 
     
    void      PushVar         (Variable newVar);
    Variable* FindVar         (const char* name);
    void      DumpDeclaredVar ();
};

class Stack
{
public:  
   std::vector <int> data;
   
public:
        Stack            ();
       ~Stack            ();
    
   int  Push             (int num);
   int  Pop              (); 
   int  Top              ();
   void Dump             ();  
};

#endif