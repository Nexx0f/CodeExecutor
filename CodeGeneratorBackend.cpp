#include "CodeGeneratorBackend.h"

int Decimal (int value)
{ 
    std::vector <int> resultValue; 
    
    int result = 0;
    while (value > 0)
    {
        resultValue.push_back (value%2);
        value /= 2;
    }
    for (int i = resultValue.size() - 1; i >= 0; i--)
         result = result * 10 + resultValue [i];
    return result;
}

unsigned char Binary (int value)
{
    std::vector <int> resultValue;
    
    int result = 0;
    while (value > 0)
    {
        resultValue.push_back (value%10);
        value /= 10;
    }
    
    for (int i = resultValue.size() - 1; i >= 0; i--)
    {
         result = result * 2 + resultValue [i];
    }
    return result;
}

ByteData::ByteData()
{

}

ByteData::~ByteData()
{

}

bool ByteData::emitByte(unsigned char byte)
{
    bytes.push_back (byte);    
}

template <typename T>
void ByteData::emitImmediate (T data)
{
    for (size_t i = 0; i < sizeof (T); i++)
    {
        emitByte (reinterpret_cast <uint8_t*> (&data) [i]);
    }
}

void ByteData::emitOpcode(opcode _opcode)
{
    int opcodeLength = _opcode.size();
    opcode::iterator opcode_it = _opcode.begin();
    
    for (int i = 0; i < opcodeLength; i++)
    {
        emitByte (*opcode_it);
        ++opcode_it;
    }   
}

//======

InstructionEmitter::InstructionEmitter(ByteData *newByteData)
{
    byteData = newByteData;
}

InstructionEmitter::InstructionEmitter()
{
    byteData = new ByteData;
}

InstructionEmitter::~InstructionEmitter()
{
    delete byteData;
}

bool InstructionEmitter::emitInstruction (opcode _opcode, GPReg dest, GPReg src)
{
    int rmByte = 11; //In the end have to be 11xxxxxx
    rmByte = rmByte * 1000 + Decimal (dest); // now r/m byte is 11abc, where "abc" - reg id
    rmByte = rmByte* 1000 + Decimal (src); // now r/m byte completed
    
    byteData -> emitByte   (BIN(1001000));
    byteData -> emitOpcode (_opcode);
    byteData -> emitByte   (rmByte);
}

bool InstructionEmitter::emitInstruction (opcode _opcode, GPReg dest, sysint_t src)
{
    byteData -> emitByte (BIN (1001000));
    
    int opcodeLength = _opcode.size();
    opcode::iterator opcode_it = _opcode.begin();
    
    for (int i = 0; i < opcodeLength; i++)
    {
        if (i == opcodeLength - 1) byteData -> emitByte (*opcode_it + dest);
        else                       byteData -> emitByte (*opcode_it);
        ++opcode_it;
    }
    
    byteData -> emitImmediate <sysint_t> (src);
}

bool InstructionEmitter::emitInstruction (opcode _opcode, int rmField, GPReg dest)
{
    int rmByte = 11;
    rmByte = rmByte * 1000 + Decimal (rmField);
    rmByte = rmByte * 1000 + Decimal (dest);
    
    byteData -> emitByte   (BIN (1001000));
    byteData -> emitOpcode (_opcode);
    byteData -> emitByte   (Binary (rmByte));
}

bool InstructionEmitter::emitInstruction (opcode _opcode)
{
    int opcodeLength = _opcode.size();
    opcode::iterator opcode_it = _opcode.begin();

    for (int i = 0; i < opcodeLength; i++)
    {
        byteData -> emitByte (*opcode_it);
        ++opcode_it;
    }
}