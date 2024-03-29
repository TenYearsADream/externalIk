#pragma once

#include "mathDefines.h"
#include "extIk.h"

class C3X3Matrix;
class C4X4Matrix;
class C7Vector;

class C3Vector  
{
public:

    C3Vector();
    C3Vector(extIkReal v0,extIkReal v1,extIkReal v2);
    C3Vector(const extIkReal v[3]);
    C3Vector(const C3Vector& v);
    ~C3Vector();

    void buildInterpolation(const C3Vector& fromThis,const C3Vector& toThat,extIkReal t);
    extIkReal getAngle(const C3Vector& v) const;
    C3X3Matrix getProductWithStar() const;

    void operator*= (const C4X4Matrix& m);
    void operator*= (const C3X3Matrix& m);
    void operator*= (const C7Vector& transf);

    inline void getInternalData(extIkReal d[3]) const
    {
        d[0]=data[0];
        d[1]=data[1];
        d[2]=data[2];
    }
    inline void setInternalData(const extIkReal d[3])
    {
        data[0]=d[0];
        data[1]=d[1];
        data[2]=d[2];
    }
    inline extIkReal* ptr()
    {
        return(data);
    }
    inline bool isColinear(const C3Vector& v,extIkReal precision) const
    {
        extIkReal scalProdSq=(*this)*v;
        scalProdSq=scalProdSq*scalProdSq;
        extIkReal l1=(*this)*(*this);
        extIkReal l2=v*v;
        return((scalProdSq/(l1*l2))>=precision);
    }
    inline extIkReal& operator() (unsigned i)
    {
        return(data[i]);
    }
    inline const extIkReal& operator() (unsigned i) const
    {
        return(data[i]);
    }
    inline extIkReal getLength() const
    {
        return(sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]));
    }
    inline void copyTo(extIkReal v[3]) const
    {
        v[0]=data[0];
        v[1]=data[1];
        v[2]=data[2];
    }
    inline void set(const extIkReal v[3])
    {
        data[0]=v[0];
        data[1]=v[1];
        data[2]=v[2];
    }
    inline void get(extIkReal v[3]) const
    {
        v[0]=data[0];
        v[1]=data[1];
        v[2]=data[2];
    }
    inline C3Vector getNormalized() const
    {
        C3Vector retV;
        extIkReal l=sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
        if (l!=0.0)
        {
            retV(0)=data[0]/l;
            retV(1)=data[1]/l;
            retV(2)=data[2]/l;
            return(retV);
        }
        return(C3Vector::zeroVector);
    }
    inline void keepMax(const C3Vector& v)
    {
        if (v(0)>data[0])
            data[0]=v(0);
        if (v(1)>data[1])
            data[1]=v(1);
        if (v(2)>data[2])
            data[2]=v(2);
    }
    inline void keepMin(const C3Vector& v)
    {
        if (v(0)<data[0])
            data[0]=v(0);
        if (v(1)<data[1])
            data[1]=v(1);
        if (v(2)<data[2])
            data[2]=v(2);
    }
    inline bool isValid() const
    {
        return((VREP_IS_FINITE(data[0])!=0)&&(VREP_IS_FINITE(data[1])!=0)&&(VREP_IS_FINITE(data[2])!=0)&&(VREP_IS_NAN(data[0])==0)&&(VREP_IS_NAN(data[1])==0)&&(VREP_IS_NAN(data[2])==0));
    }
    inline void set(extIkReal v0,extIkReal v1,extIkReal v2)
    {
        data[0]=v0;
        data[1]=v1;
        data[2]=v2;
    }
    inline void normalize()
    {
        extIkReal l=sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
        if (l!=0.0)
        {
            data[0]=data[0]/l;
            data[1]=data[1]/l;
            data[2]=data[2]/l;
        }
    }
    inline void clear()
    {
        data[0]=0.0;
        data[1]=0.0;
        data[2]=0.0;
    }
    inline C3Vector operator/ (extIkReal d) const
    {
        C3Vector retV;
        retV(0)=data[0]/d;
        retV(1)=data[1]/d;
        retV(2)=data[2]/d;
        return(retV);
    }
    inline void operator/= (extIkReal d)
    {
        data[0]/=d;
        data[1]/=d;
        data[2]/=d;
    }
    inline C3Vector operator* (extIkReal d) const
    {
        C3Vector retV;
        retV(0)=data[0]*d;
        retV(1)=data[1]*d;
        retV(2)=data[2]*d;
        return(retV);
    }
    inline void operator*= (extIkReal d)
    {
        data[0]*=d;
        data[1]*=d;
        data[2]*=d;
    }
    inline C3Vector& operator= (const C3Vector& v)
    {
        data[0]=v(0);
        data[1]=v(1);
        data[2]=v(2);
        return(*this);
    }
    inline bool operator!= (const C3Vector& v)
    {
        return( (data[0]!=v(0))||(data[1]!=v(1))||(data[2]!=v(2)) );
    }
    inline C3Vector operator+ (const C3Vector& v) const
    {
        C3Vector retV;
        retV(0)=data[0]+v(0);
        retV(1)=data[1]+v(1);
        retV(2)=data[2]+v(2);
        return(retV);
    }
    inline void operator+= (const C3Vector& v)
    {
        data[0]+=v(0);
        data[1]+=v(1);
        data[2]+=v(2);
    }
    inline C3Vector operator- (const C3Vector& v) const
    {
        C3Vector retV;
        retV(0)=data[0]-v(0);
        retV(1)=data[1]-v(1);
        retV(2)=data[2]-v(2);
        return(retV);
    }
    inline void operator-= (const C3Vector& v)
    {
        data[0]-=v(0);
        data[1]-=v(1);
        data[2]-=v(2);
    }
    inline C3Vector operator^ (const C3Vector& v) const
    { // Cross product
        C3Vector retV;
        retV(0)=data[1]*v(2)-data[2]*v(1);
        retV(1)=data[2]*v(0)-data[0]*v(2);
        retV(2)=data[0]*v(1)-data[1]*v(0);
        return(retV);
    }
    inline void operator^= (const C3Vector& v)
    { // Cross product
        C3Vector retV;
        retV(0)=data[1]*v(2)-data[2]*v(1);
        retV(1)=data[2]*v(0)-data[0]*v(2);
        retV(2)=data[0]*v(1)-data[1]*v(0);
        data[0]=retV(0);
        data[1]=retV(1);
        data[2]=retV(2);
    }
    inline extIkReal operator* (const C3Vector& v) const
    { // Scalar product
        return(data[0]*v.data[0]+data[1]*v.data[1]+data[2]*v.data[2]);
    }

    static const C3Vector oneOneOneVector;
    static const C3Vector unitXVector;
    static const C3Vector unitYVector;
    static const C3Vector unitZVector;
    static const C3Vector zeroVector;

    extIkReal data[3];
};




