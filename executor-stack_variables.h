const int MAX_VARIABLES_AMOUNT = 1000;
const int MAX_STACK_SIZE = 1000;

const int UNDERFLOWN = 1;
const int OVERFLOWN  = 2;

struct Variable
{
    char* name;
    int value;   
};

class VariablesData
{
public:
    Variable data [MAX_VARIABLES_AMOUNT];
    int currAmountVar;
     
    VariablesData ();       
     
    void PushVar (Variable newVar);
     
    Variable* FindVar (const char* name);
     
    void DumpDeclaredVar ();
};

class Stack
{
public:  
   int data [MAX_STACK_SIZE];
   int size;
   int error_number;
    
public:
   Stack                 ();
    
   int  Ok               ();
   int  Push             (int num);
   int  Pop              (); 
   int  Top              ();
   void Dump             ();
   int  GetYourLastError ();   
};