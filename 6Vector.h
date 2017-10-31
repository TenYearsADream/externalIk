#pragma once

#include "mathDefines.h"
#include "extIk.h"
#include "3Vector.h"

class C6X6Matrix;

class C6Vector  
{
public:
    C6Vector();
    C6Vector(extIkReal v0,extIkReal v1,extIkReal v2,extIkReal v3,extIkReal v4,extIkReal v5);
    C6Vector(const extIkReal v[6]);
    C6Vector(const C3Vector& v0,const C3Vector& v1);
    C6Vector(const C6Vector& v);
    ~C6Vector();

    void clear();
    C6X6Matrix getSpatialCross() const;

    C6Vector operator* (extIkReal d) const;
    C6Vector operator/ (extIkReal d) const;
    C6Vector operator+ (const C6Vector& v) const;
    C6Vector operator- (const C6Vector& v) const;

    void operator*= (extIkReal d);
    void operator/= (extIkReal d);
    void operator+= (const C6Vector& v);
    void operator-= (const C6Vector& v);

    extIkReal operator* (const C6Vector& v) const;
    C6Vector& operator= (const C6Vector& v);

    inline void getInternalData(extIkReal d[6]) const
    {
        V[0].getInternalData(d+0);
        V[1].getInternalData(d+3);
    }
    inline void setInternalData(const extIkReal d[6])
    {
        V[0].setInternalData(d+0);
        V[1].setInternalData(d+3);
    }
    inline extIkReal& operator() (unsigned i)
    {
        if (i<3)
            return(V[0](i));
        else
            return(V[1](i-3));
    }
    inline const extIkReal& operator() (unsigned i) const
    {
        if (i<3)
            return(V[0](i));
        else
            return(V[1](i-3));
    }

    C3Vector V[2];
};
