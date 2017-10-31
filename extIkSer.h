#pragma once

#include "extIk.h"
#include <vector>

class CExtIkSer  
{
public:

    CExtIkSer(unsigned char* data,int dataLength); // reading


    virtual ~CExtIkSer();


    float readFloat();
    int readInt();
    unsigned int readUInt();
    unsigned short readWord();
    unsigned char readByte();
    char readChar();
    std::string readString();

private:
    bool _reading;

    unsigned char* _readBuffer;
    int _readBufferLength;
    int _readLocation;
};