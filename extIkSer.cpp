#include "extIkSer.h"


CExtIkSer::CExtIkSer(unsigned char* data,int dataLength)
{
    _reading=true;
    _readBuffer=data;
    _readBufferLength=dataLength;
    _readLocation=0;
}

CExtIkSer::~CExtIkSer()
{
}



float CExtIkSer::readFloat()
{
    unsigned char tmp[4];
    tmp[0]=_readBuffer[_readLocation++];
    tmp[1]=_readBuffer[_readLocation++];
    tmp[2]=_readBuffer[_readLocation++];
    tmp[3]=_readBuffer[_readLocation++];
    return(((float*)(&tmp))[0]);
}

int CExtIkSer::readInt()
{
    unsigned char tmp[4];
    tmp[0]=_readBuffer[_readLocation++];
    tmp[1]=_readBuffer[_readLocation++];
    tmp[2]=_readBuffer[_readLocation++];
    tmp[3]=_readBuffer[_readLocation++];
    return(((int*)(&tmp))[0]);
}

unsigned int CExtIkSer::readUInt()
{
    unsigned char tmp[4];
    tmp[0]=_readBuffer[_readLocation++];
    tmp[1]=_readBuffer[_readLocation++];
    tmp[2]=_readBuffer[_readLocation++];
    tmp[3]=_readBuffer[_readLocation++];
    return(((unsigned int*)(&tmp))[0]);
}

unsigned short CExtIkSer::readWord()
{
    unsigned char tmp[2];
    tmp[0]=_readBuffer[_readLocation++];
    tmp[1]=_readBuffer[_readLocation++];
    return(((unsigned short*)(&tmp))[0]);
}

unsigned char CExtIkSer::readByte()
{
    return(_readBuffer[_readLocation++]);
}

char CExtIkSer::readChar()
{
    return((char)_readBuffer[_readLocation++]);
}

std::string CExtIkSer::readString()
{
    std::string retVal;
    while (_readBuffer[_readLocation]!=0)
        retVal+=(char)_readBuffer[_readLocation++];
    _readLocation++; // terminal zero
    return(retVal);
}
