#ifndef H_EXECUTOR-STACK_VARIABLES
#define H_EXECUTOR-STACK_VARIABLES

#include <vector>
#include <map>
#include <string>
#include "AsmJit/AsmJit.h"

struct Variable
{
    const char* name;
    sysint_t value;   
};

class VariablesData
{
public:
    std::map <std::string, Variable> data;
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
   std::vector <sysint_t> data;
   
public:
        Stack            ();
       ~Stack            ();
    
   int       Push             (sysint_t num);
   sysint_t  Pop              (); 
   int       Top              ();
   void      Dump             ();  
};

#endif