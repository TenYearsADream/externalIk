
#pragma once

#include "mathDefines.h"

class VPoint
{
public:
    VPoint()    {}
    VPoint(int initX,int initY) { x=initX; y=initY; }
    virtual ~VPoint()   {}
    int x,y;
};
