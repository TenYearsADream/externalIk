
#pragma once

#include "mathDefines.h"
#include "extIk.h"
#include "4X4Matrix.h"
#include "3Vector.h"

class C4X4FullMatrix  
{
public:
    C4X4FullMatrix();
    C4X4FullMatrix(const C4X4Matrix& m);
    C4X4FullMatrix(const C4X4FullMatrix& m);
    ~C4X4FullMatrix();

    void invert();
    void clear();
    void setIdentity();
    void buildZRotation(extIkReal angle);
    void buildTranslation(extIkReal x, extIkReal y, extIkReal z);
    C3Vector getEulerAngles() const;

    C4X4FullMatrix operator* (const C4X4FullMatrix& m) const;
    C4X4FullMatrix operator* (extIkReal d) const;
    C4X4FullMatrix operator/ (extIkReal d) const;
    C4X4FullMatrix operator+ (const C4X4FullMatrix& m) const;
    C4X4FullMatrix operator- (const C4X4FullMatrix& m) const;
    
    void operator*= (const C4X4FullMatrix& m);
    void operator+= (const C4X4FullMatrix& m);
    void operator-= (const C4X4FullMatrix& m);
    void operator*= (extIkReal d);
    void operator/= (extIkReal d);

    C4X4FullMatrix& operator= (const C4X4Matrix& m);
    C4X4FullMatrix& operator= (const C4X4FullMatrix& m);

    inline extIkReal& operator() (int row,int col)
    {
        return(data[row][col]);
    }
    inline const extIkReal& operator() (int row,int col) const
    {
        return(data[row][col]);
    }
        
private:
    extIkReal data[4][4];
};

