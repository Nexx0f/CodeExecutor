#include "ByteData.h"

ByteData::ByteData()
{

}

ByteData::~ByteData()
{

}

bool ByteData::emitByte (unsigned char byte)
{
    bytes.push_back (byte);    
}


void ByteData::emitOpcode (opcode _opcode)
{
    int opcodeLength = _opcode.size();
    opcode::iterator opcode_it = _opcode.begin();
    
    for (int i = 0; i < opcodeLength; i++)
    {
        emitByte (*opcode_it);
        ++opcode_it;
    }   
}