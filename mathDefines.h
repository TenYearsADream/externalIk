#pragma once

#include <math.h>
#include <limits>
#include <float.h>
#include <cstdlib>

#ifdef MAC_VREP
#include <boost/math/special_functions/fpclassify.hpp>
#endif

#ifdef EXTIK_DOUBLE
    typedef double extIkReal;
#else
    typedef float extIkReal;
#endif

const extIkReal piValue=(extIkReal)3.14159265359;
const extIkReal piValTimes2=(extIkReal)6.28318530718;
const extIkReal piValD2=(extIkReal)1.57079632680;
const extIkReal radToDeg=(extIkReal)57.2957795130785499;
const extIkReal degToRad=(extIkReal)0.017453292519944444;
const extIkReal IK_DIVISION_FACTOR=(extIkReal)100.0;
#ifdef EXTIK_DOUBLE
const extIkReal extIkMaxReal=0.01*DBL_MAX;
#else
const extIkReal extIkMaxReal=0.01f*FLT_MAX;
#endif
