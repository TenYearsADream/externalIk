
#include "Tt.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "MyMath.h"

extIkReal tt::getNormalizedAngle(extIkReal angle)
{ // Returns an angle between -PI and +PI
    extIkReal sinAngle=sin(angle);
    extIkReal cosAngle=cos(angle);
    extIkReal angle_da=atan2(sinAngle,cosAngle);
    return(angle_da);
}

int tt::getLimitedInt(int minValue,int maxValue,int value)
{
    if (value>maxValue)
        value=maxValue;
    if (value<minValue)
        value=minValue;
    return(value);
}

void tt::limitValue(int minValue,int maxValue,int &value)
{
    if (value>maxValue)
        value=maxValue;
    if (value<minValue)
        value=minValue;
}

extIkReal tt::getLimitedFloat(extIkReal minValue,extIkReal maxValue,extIkReal value)
{
    if (value>maxValue)
        value=maxValue;
    if (value<minValue)
        value=minValue;
    return(value);
}

void tt::limitValue(extIkReal minValue,extIkReal maxValue,extIkReal &value)
{
    if (value>maxValue)
        value=maxValue;
    if (value<minValue)
        value=minValue;
}
