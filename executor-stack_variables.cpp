#include "executor-stack_variables.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void MessageAboutError (const char* string)
{
    printf ("\n\n ==Error==>>>>>> %s <<<<<<==Error==", string);
}

VariablesData::VariablesData()
{
      currAmountVar = 0;
}
         
void VariablesData::PushVar (Variable newVar)
{
    data[currAmountVar] = newVar;
    if (currAmountVar + 1 >= MAX_VARIABLES_AMOUNT) 
       MessageAboutError ("Stack data UNDERFLOWNn");
    else currAmountVar++;

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

Stack::Stack()
{
    size = 0;
    error_number = 0;
}   

int Stack::Ok()
{
    if (size > MAX_STACK_SIZE)
    {
        error_number = OVERFLOWN;
        return 0;
    }
    if (size < 0)
    {
        error_number = UNDERFLOWN;
        return 0;
    }
    return !0;            
    
}

int Stack::Push (int num)
{
    Ok();
    data[size] = num;
    size++;
    assert (Ok());
    return error_number;
}
    
int Stack::Pop()
{
    Ok();
    int num = 0;
    size--;
    num = data[size];
    assert (Ok());
    return num;
} 

int Stack::Top()
{
    Ok();
    int num = 0;
    num = data[size-1];
    Ok();
    return num; 
}

void Stack::Dump()
{
    Ok();
    printf ("Class Stack\nsize = %d, maxsize = %d\n"
            "{\n    Printing data...\n", size, MAX_STACK_SIZE);
    for (int i = 0; i < MAX_STACK_SIZE; i++)
    {
        if (i <  size) 
        {  
            printf ("     *[%d] = %d\n", i, data[i]);
        }
        
        if (i >= size) 
        {
            printf ("      [%d] = %d\n", i, data[i]);
        }
    }
    puts ("}");
    assert (Ok());

}    
int Stack::GetYourLastError()
{
    return error_number;

}    