#include "DataTypes.h"
#include <vector>
#include <stdio.h>

class ByteData
{
public:    
    std::vector <unsigned char> bytes;

public:
    ByteData ();
   ~ByteData ();
   
    bool emitByte (unsigned char byte);
    
    template <typename T>
    void emitImmediate (T data)
    {
        for (size_t i = 0; i < sizeof (T); i++)
        {
            emitByte (reinterpret_cast <uint8_t*> (&data) [i]);
        }
    }
    
    void emitOpcode    (opcode _opcode);
};