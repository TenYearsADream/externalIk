
#include "MyMath.h"

CMath::CMath()
{
}

CMath::~CMath()
{
}

void CMath::limitValue(extIkReal minValue,extIkReal maxValue,extIkReal &value)
{
    if (value>maxValue)
        value=maxValue;
    if (value<minValue) 
        value=minValue;
}

void CMath::limitValue(int minValue,int maxValue,int &value)
{
    if (value>maxValue) 
        value=maxValue;
    if (value<minValue) 
        value=minValue;
}

extIkReal CMath::robustAsin(extIkReal v)
{
    if (!isNumberOk(v))
        return(0.0);
    if (v>=1.0)
        return(piValue*(extIkReal)0.5);
    if (v<=-1.0)
        return(-piValue*(extIkReal)0.5);
    return(asin(v));
}

extIkReal CMath::robustAcos(extIkReal v)
{
    if (!isNumberOk(v))
        return(0.0);
    if (v>=1.0)
        return(0.0);
    if (v<=-1.0)
        return(piValue);
    return(acos(v));
}

bool CMath::isNumberOk(extIkReal v)
{
    return ( (!VREP_IS_NAN(v))&&(fabs(v)!=std::numeric_limits<extIkReal>::infinity()) );    
}
