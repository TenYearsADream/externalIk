#pragma once

#include "extIk.h"
#include "3Vector.h"
#include "4Vector.h"
#include "6Vector.h"
#include "7Vector.h"
#include "Vector.h"
#include "3X3Matrix.h"
#include "4X4Matrix.h"
#include "6X6Matrix.h"
#include "4X4FullMatrix.h"
#include "MMatrix.h"

class CMath  
{
public:
    CMath();
    virtual ~CMath();

    static void limitValue(extIkReal minValue,extIkReal maxValue,extIkReal &value);
    static void limitValue(int minValue,int maxValue,int &value);


    static extIkReal robustAsin(extIkReal v);
    static extIkReal robustAcos(extIkReal v);
    static bool isNumberOk(extIkReal v);
};
