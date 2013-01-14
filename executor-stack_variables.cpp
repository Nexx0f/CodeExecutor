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
    data.push_back (newVar);
    currAmountVar++;

}

Variable* VariablesData::FindVar (const char* name)
{
    for (int i = currAmountVar - 1; i >= 0; i--)
    {
        if (!strcmp (data[i].name, name)) return &data[i];
    }
          
          
    char errorStr [256] = "";
    sprintf (errorStr, "Variable \"%s\" not declared", name);
          
    MessageAboutError (errorStr);
}

void VariablesData::DumpDeclaredVar()
{
    puts ("\n\n\n\n\n\n");
    for (int i = 0; i < currAmountVar; i++)
    {
        puts ("\nVariable\n{\n");
        printf ("    name  - \"%s\" \n"
                "    value - %d\n}\n", data[i].name, data[i].value);
    }
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

int Stack::Push (int num)
{
    data.push_back (num);
}
    
int Stack::Pop()
{
    int num = 0;
    num = data[data.size()-1];
    
    if (data.size() == 0)
        MessageAboutError ("Stack underflown!");
    
    data.pop_back();
    return num;
} 

int Stack::Top()
{
    int num = 0;
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