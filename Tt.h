#pragma once

#include <string>
#include <vector>
#include "MMatrix.h"

class tt  
{

public:
    static extIkReal getNormalizedAngle(extIkReal angle);
    static int getLimitedInt(int minValue,int maxValue,int value);
    static void limitValue(int minValue,int maxValue,int &value);
    static extIkReal getLimitedFloat(extIkReal minValue,extIkReal maxValue,extIkReal value);
    static void limitValue(extIkReal minValue,extIkReal maxValue,extIkReal &value);
};
