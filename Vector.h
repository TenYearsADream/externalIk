
#pragma once

#include "mathDefines.h"
#include "extIk.h"
#include "3Vector.h"
#include "4Vector.h"
#include "6Vector.h"
#include "7Vector.h"

class CVector  
{
public:
    CVector();
    CVector(int nElements);
    CVector(const C3Vector& v);
    CVector(const C4Vector& v);
    CVector(const C6Vector& v);
    CVector(const C7Vector& v);
    CVector(const CVector& v);
    ~CVector();

    CVector operator* (extIkReal d) const;
    CVector operator/ (extIkReal d) const;
    CVector operator+ (const CVector& v) const;
    CVector operator- (const CVector& v) const;

    void operator*= (extIkReal d);
    void operator/= (extIkReal d);
    void operator+= (const CVector& v);
    void operator-= (const CVector& v);
    
    extIkReal operator* (const C3Vector& v) const;
    extIkReal operator* (const C4Vector& v) const;
    extIkReal operator* (const C6Vector& v) const;
    extIkReal operator* (const C7Vector& v) const;
    extIkReal operator* (const CVector& v) const;

    CVector& operator= (const C3Vector& v);
    CVector& operator= (const C4Vector& v);
    CVector& operator= (const C6Vector& v);
    CVector& operator= (const C7Vector& v);
    CVector& operator= (const CVector& v);

inline extIkReal& operator() (int i)
{
    return(data[i]);
}

inline const extIkReal& operator() (int i) const
{
    return(data[i]);
}

    int elements;
private:
    extIkReal* data;
};

