#include "executor-stack_variables.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void MessageAboutError (const char* string)
{
    printf ("\n\n ==Error==>>>>>> %s <<<<<<==Error==", string);
    assert (0);
}

VariablesData::VariablesData()
{
    currAmountVar = 0;
}
 
VariablesData::~VariablesData()
{
} 
 
void VariablesData::PushVar (Variable newVar)
{
    //data.push_back (newVar);
    //currAmountVar++;
    std::string newName (newVar.name);
    data [newName] = newVar;
}

Variable* VariablesData::FindVar (const char* name)
{
    std::string needName (name);
    std::map <std::string, Variable>::iterator foundVar = data.find(needName);      
    
    if (foundVar == data.end())
    {
        char errorStr [256] = "";
        sprintf (errorStr, "Variable \"%s\" not declared", name);
          
        MessageAboutError (errorStr);
    }
    else return &(foundVar -> second);
}

void VariablesData::DumpDeclaredVar()
{
   // puts ("\n\n\n\n\n\n");
   // for (int i = 0; i < currAmountVar; i++)
   // {
   //     puts ("\nVariable\n{\n");
   //     printf ("    name  - \"%s\" \n"
   //             "    value - %d\n}\n", data[i].name, data[i].value);
   // }
   
}

/////=================================
/* Processors stack emulator */
/////=================================

Stack::Stack()
{
}   

Stack::~Stack()
{
}

int Stack::Push (sysint_t num)
{
    data.push_back (num);
}
    
sysint_t Stack::Pop()
{
    //printf ("\nProcess pop; Size - %d\n", data.size());
    
    if (data.size() == 0)
        MessageAboutError ("Stack underflown!");
        
    sysint_t num = 0;
    num = data[data.size()-1];
    
    data.pop_back();
    return num;
} 

int Stack::Top()
{
    sysint_t num = 0;
    num = data[data.size() - 1];

    return num; 
}

void Stack::Dump()
{
    printf ("Class Stack\nsize = %d"
            "{\n    Printing data...\n", data.size());
    for (int i = 0; i < data.size(); i++)
    {
        printf ("     *[%d] = %d\n", i, data[i]);
    }
    puts ("}");
}      