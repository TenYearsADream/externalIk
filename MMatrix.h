
#pragma once

#include "mathDefines.h"
#include "extIk.h"
#include "3X3Matrix.h"
#include "4X4Matrix.h"
#include "6X6Matrix.h"
#include "Vector.h"

class CMatrix  
{
public:
    CMatrix();
    CMatrix(int nRows,int nCols);
    CMatrix(const C3X3Matrix& m);
    CMatrix(const C4X4Matrix& m);
    CMatrix(const C6X6Matrix& m);
    CMatrix(const CMatrix& m);
    ~CMatrix();

    bool inverse();
    void transpose();
    void clear();
    void setIdentity();

    CMatrix operator* (const C3X3Matrix& m) const;
    CMatrix operator* (const C4X4Matrix& m) const;
    CMatrix operator* (const C6X6Matrix& m) const;
    CMatrix operator* (const CMatrix& m) const;
    CMatrix operator* (extIkReal d) const;
    CMatrix operator/ (extIkReal d) const;
    CVector operator* (const CVector& v) const;
    CMatrix operator+ (const CMatrix& m) const;
    CMatrix operator- (const CMatrix& m) const;
    
    void operator*= (const CMatrix& m);
    void operator+= (const CMatrix& m);
    void operator-= (const CMatrix& m);
    void operator*= (extIkReal d);
    void operator/= (extIkReal d);

    CMatrix& operator= (const C3X3Matrix& m);
    CMatrix& operator= (const C4X4Matrix& m);
    CMatrix& operator= (const C6X6Matrix& m);
    CMatrix& operator= (const CMatrix& m);

inline extIkReal& operator() (int row,int col)
{
    return(data[row*cols+col]);
}

inline extIkReal getAt(int row,int col) const
{
    return(data[row*cols+col]);
}

inline void setAt(int row,int col,extIkReal value)
{
    data[row*cols+col]=value;
}
 
inline const extIkReal& operator() (int row,int col) const
{
    return(data[row*cols+col]);
}


    int rows,cols;
    extIkReal* data;
};


