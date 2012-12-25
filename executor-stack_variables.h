#include <vector>

struct Variable
{
    const char* name;
    int value;   
};

class VariablesData
{
public:
    std::vector <Variable> data;
    int currAmountVar;
     
    VariablesData ();       
     
    void PushVar (Variable newVar);
     
    Variable* FindVar (const char* name);
     
    void DumpDeclaredVar ();
};

class Stack
{
public:  
   std::vector <int> data;
public:
   Stack                 ();
    
   int  Push             (int num);
   int  Pop              (); 
   int  Top              ();
   void Dump             ();  
};