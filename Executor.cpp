#include "Executor.h"
#include <stdio.h>
#include "string.h"
#include <iostream>
#include <fstream>
#include <conio.h>

Executor::Executor()
{
    dataSize = 0;
    stack = new Stack;
    varData = new VariablesData;
}

Executor::Executor (FILE* inF)
{
    dataSize = 0;
    stack = new Stack;
    varData = new VariablesData;
    loadFile (inF);
}

void Executor::loadFile (FILE* inF)
{
    using namespace Commands;
    
    int rStr = 0;
    
    while (!feof (inF))
    {
          fscanf (inF, "%d ", &data[dataSize]);
          dataSize+=1;
          if ((data[dataSize-1] < 100) &&
              (data[dataSize-1] != POPTO) &&
              (data[dataSize-1] != PUSHFROM) &&
              (data[dataSize-1] != LABEL)) fscanf (inF, "%d", &data[dataSize]);
          else data[dataSize] = 0;
          
          if (data[dataSize-1] == DECL)
          {
               Variable newVar;
               char name [256] = ""; 
               fscanf (inF, " %s", &name);
               
               newVar.name = new char [strlen (name) + 1];
               strcpy (newVar.name, name);
               
               varData -> PushVar (newVar);
          }
          
          
          if ((data[dataSize-1] == LABEL) ||
              (data[dataSize-1] == JUMP) ||
              (data[dataSize-1] == JB) ||
              (data[dataSize-1] == JA) ||
              (data[dataSize-1] == JBE) ||
              (data[dataSize-1] == JAE) ||
              (data[dataSize-1] == JE) ||
              (data[dataSize-1] == JNE) ||
              (data[dataSize-1] == CALL))
          {
               char name [256] = ""; 
               fscanf (inF, " %s", &name);
               
               stringArguments[rStr] = new char [strlen (name) + 1];
               strcpy (stringArguments[rStr], name);               
               
               data[dataSize] = rStr;
               
               rStr++;     
          } 
              
          if ((data[dataSize-1] == POPTO) ||
              (data[dataSize-1] == PUSHFROM))
          {
               char name [256] = ""; 
               fscanf (inF, " %s", &name); 
               
               stringArguments[rStr] = new char [strlen (name) + 1];
               strcpy (stringArguments[rStr], name);
               rStr++;             
          }          
          dataSize+=1;
          //printf ("%d %d\n", data[dataSize-2], data[dataSize-1]);
    }
}

void Executor::Execute()
{
    using namespace Commands;
    int rStr = 0; 
    
    printf ("\nTranslating completed.\n"
            "Starting to execute. Output:\n", dataSize);
    
    for (int i = 0; i < dataSize; i++)
    {
        //printf ("\ndata[i] = %d i = %d\n", data[i], i);
        if (data[i] == PUSH)
        {
            stack->Ok ();
            int n = data[i+1];
            stack->Push (n);
            i+=1;
            stack->Ok();
        }
        
        else
        if (data[i] == LABEL)
        {
            stack->Ok ();
            i+=1;
            rStr++;
            stack->Ok();
        } 
        
        else
        if ((data[i] == JUMP) ||
            (data[i] == JB) ||
            (data[i] == JA) ||
            (data[i] == JBE) ||
            (data[i] == JAE) ||
            (data[i] == JE) ||
            (data[i] == JNE) ||
            (data[i] == CALL))
        {
            stack->Ok ();
            
            char* label = new char [strlen (stringArguments [data[i+1]]) + 1];
            strcpy (label, stringArguments [data[i+1]]);
            i+=1;
            
            int num = 0;
            
            for (int x = 0; x < dataSize-1; x+=2)
                 if (data[x] == LABEL && !strcmp (stringArguments [data[x+1]], label)) num = x+2;
                 
            bool jum = false;
            
            if ((data[i-1] == JUMP)) jum = true;
            else
            if ((data[i-1] == CALL)) 
            {
                jum = true;
                retStack.Push (rStr+1);
                retStack.Push (i);
                
            }
            else
            {
                int datai  = stack->Pop();
                int datai1 = stack->Pop();
            
                if ((data[i-1] == JB) &&  (datai > datai1)) jum = true;  
                if ((data[i-1] == JA) &&  (datai < datai1)) jum = true;
                if ((data[i-1] == JBE) && (datai >= datai1)) jum = true;
                if ((data[i-1] == JAE) && (datai <= datai1)) jum = true;
                if ((data[i-1] == JE) &&  (datai == datai1)) jum = true;
                if ((data[i-1] == JNE) && (datai != datai1)) jum = true;
            
                stack->Push (datai1);
                stack->Push (datai);
            }
            
            if (num == 0) 
            {
                    char str[100] = "";
                    sprintf (str, "Label %s was not found", label);
                    printf ("\nExecution error:\n======>>>>>>%s<<<<<<======", str);
                    return;
            }
            else
            if (jum) 
            {
                     i = num - 1;
                     rStr = data [i] + 1;
      //puts ("All good we are jumped...\n");
        //  getch();               
            }
            else {rStr++;}
                 
            stack->Ok();
        }               
        else              
        if (data[i] == DUMP)
        {
            stack->Ok ();
            stack->Dump ();
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == ADD)
        {
            stack->Ok ();
            stack->Push (stack->Pop() + stack->Pop());
            i+=1;
            stack->Ok();
        }  
        else
        if (data[i] == MUL)
        {
            stack->Ok ();
            stack->Push (stack->Pop() * stack->Pop());
            i+=1;
            stack->Ok();
        }  
        else
        if (data[i] == DIV)
        {
            stack->Ok ();
            stack->Push (stack->Pop() / stack->Pop());
            i+=1;
            stack->Ok();
        }                     
        else
        if (data[i] == SUB)
        {
            stack->Ok ();
            stack->Push (stack->Pop() - stack->Pop());
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == TOP)
        {
            stack->Ok ();
            printf ("%d\n", stack->Top());
            i+=1;
            stack->Ok();
        } 
        else
        if (data[i] == DUP)
        {
            stack->Ok ();
            stack->Push (stack->Top());
            i+=1;
            stack->Ok();
        }             
        else
        if (data[i] == HELP)
        {
            stack->Ok ();
            printf ("HELP IS NOT AVALIBLE IN THIS VERSION =)\n");
            i+=1;
            stack->Ok();
        } 
        else
        if (data[i] == CLEAR)
        {
            stack->Ok ();
            stack->size = 0;
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == CLS)
        {
            stack->Ok ();
            for (int i = 0; i < 100; i++) printf ("\n");
            i+=1;
            stack->Ok();
        }

        else
        if (data[i] == POP)
        {
            stack->Ok ();
            i+=1;
            stack->Ok();
        }
        
        else
        if (data[i] == GETCH)
        {
            //using namespace std;
            stack->Ok ();
            
            getch();
            
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == DECL)
        {
            stack->Ok ();
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == POPTO)
        {
            stack->Ok ();
            Variable* x = varData -> FindVar (stringArguments[rStr]);
            rStr++;
            x -> value = stack -> Pop(); 
            i+=1;
            stack->Ok();
        }
        else
        if (data[i] == PUSHFROM)
        {
            stack->Ok ();
            Variable* x = varData -> FindVar (stringArguments[rStr]);
            rStr++;
            stack -> Push (x -> value);
            i+=1;
            stack->Ok();
        }                
        else
        if (data[i] == MOREEQUAL)
        {
            stack->Ok ();
            int i2 = stack -> Pop ();
            int i1 = stack -> Pop ();
            
            if (i1 >= i2) stack -> Push (1);
            else          stack -> Push (0);
            i+=1;
            stack->Ok();
        }   
        else
        if (data[i] == LESSEQUAL)
        {
            stack->Ok ();
            int i2 = stack -> Pop ();
            int i1 = stack -> Pop ();
            
            if (i1 <= i2) stack -> Push (1);
            else          stack -> Push (0);
            i+=1;
            stack->Ok();
        }         
        else
        if (data[i] == MORE)
        {
            stack->Ok ();
            int i2 = stack -> Pop ();
            int i1 = stack -> Pop ();
            
            if (i1 > i2) stack -> Push (1);
            else          stack -> Push (0);
            i+=1;
            stack->Ok();
        } 
        else
        if (data[i] == LESS)
        {
            stack->Ok ();
            int i2 = stack -> Pop ();
            int i1 = stack -> Pop ();
            
            if (i1 < i2)  stack -> Push (1);
            else          stack -> Push (0);
            i+=1;
            stack->Ok();
        } 
        else
        if (data[i] == EQUAL)
        {
            stack->Ok ();
            int i2 = stack -> Pop ();
            int i1 = stack -> Pop ();
            
            if (i2 == i1) stack -> Push (1);
            else          stack -> Push (0);
            i+=1;
            stack->Ok();
        } 
        else
        if (data[i] == RET)
        {
            stack->Ok();
            i    = retStack.Pop();
            rStr = retStack.Pop();
            stack->Ok();        
        }                                         
        else
        {
            char errData [256];
            sprintf (errData, "Unknown command. Command code - %d."
                              " Iterator - %d. Size - %d", data[i], i, dataSize);
            printf ("\nExecution error:\n======>>>>>>%s<<<<<<======", errData);
            return;
        }
    }                  
}