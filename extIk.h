
#pragma once

#include <math.h>
#include <vector>
#include <string>
#include <float.h>
#include <limits>
#include "mathDefines.h"

#define VREP_INLINE inline
#define SIM_ASSERT(x)
#define SIM_IS_BIT_SET(var,bit) (((var) & (1<<(bit)))!=0)

#ifdef _WIN32
    #define VREP_IS_FINITE(x) (_finite(x))
    #define VREP_IS_NAN(x) (_isnan(x))
#endif // _WIN32

#ifdef __APPLE__
    #include <boost/math/special_functions/fpclassify.hpp>
    #define VREP_IS_FINITE(x) (finite(x))
    #define VREP_IS_NAN(x) ((boost::math::isnan)(x))
#endif // __APPLE__

#ifdef __linux
    #define VREP_IS_NAN(x) (isnan(x))
    #define VREP_IS_FINITE(x)                           \
            (sizeof (x) == sizeof (float)                   \
            ? __finitef (x)                                 \
            : sizeof (x) == sizeof (double)                 \
            ? __finite (x) : __finitel (x))
#endif // __linux

int simEmbLaunch();
int simEmbShutDown();
bool simEmbSwitch(int handle);
int simEmbStart(unsigned char* data,int dataLength);

int simEmbGetObjectHandle(const char* objectName);
int simEmbGetObjectParent(int objectHandle);
int simEmbSetObjectParent(int objectHandle,int parentObjectHandle,bool keepInPlace);

int simEmbGetJointPosition(int jointHandle,extIkReal* position);
int simEmbSetJointPosition(int jointHandle,extIkReal position);
int simEmbGetJointTransformation(int jointHandle,extIkReal* position,extIkReal* quaternion);
int simEmbGetJointMatrix(int jointHandle,extIkReal* matrix);
int simEmbSetSphericalJointQuaternion(int jointHandle,const extIkReal* quaternion);
int simEmbSetSphericalJointMatrix(int jointHandle,const extIkReal* matrix);
int simEmbSetJointMode(int jointHandle,int jointMode);
int simEmbGetJointInterval(int jointHandle,extIkReal* interval);
int simEmbSetJointInterval(int jointHandle,int cyclic,const extIkReal* interval);

int simEmbGetIkGroupHandle(const char* ikGroupName);
int simEmbHandleIkGroup(int ikGroupHandle);
int simEmbSetIkGroupExplicitHandling(int ikGroupHandle,bool explicitHandling);
int simEmbSetIkGroupProperties(int ikGroupHandle,int resolutionMethod,int maxIterations,extIkReal damping);
int simEmbSetIkElementProperties(int ikGroupHandle,int tipDummyHandle,int constraints,const extIkReal* precision,const extIkReal* weight);
int simEmbGetConfigForTipPose(int ikGroupHandle,int jointCnt,const int* jointHandles,extIkReal thresholdDist,int maxIterations,extIkReal* retConfig,const extIkReal* metric,const int* jointOptions,void* reserved);

int simEmbGetObjectTransformation(int objectHandle,int relativeToObjectHandle,extIkReal* position,extIkReal* quaternion);
int simEmbGetObjectMatrix(int objectHandle,int relativeToObjectHandle,extIkReal* matrix);
int simEmbSetObjectTransformation(int objectHandle,int relativeToObjectHandle,const extIkReal* position,const extIkReal* quaternion);
int simEmbSetObjectMatrix(int objectHandle,int relativeToObjectHandle,const extIkReal* matrix);
int simEmbQuaternionToEulerAngles(const extIkReal* quaternion,extIkReal* euler);
int simEmbEulerAnglesToQuaternion(const extIkReal* euler,extIkReal* quaternion);
int simEmbTransformationToMatrix(const extIkReal* position,const extIkReal* quaternion,extIkReal* matrix);
int simEmbMatrixToTransformation(const extIkReal* matrix,extIkReal* position,extIkReal* quaternion);
int simEmbInvertTransformation(extIkReal* position,extIkReal* quaternion);
int simEmbInvertMatrix(extIkReal* matrix);
int simEmbMultiplyTransformations(const extIkReal* position1,const extIkReal* quaternion1,const extIkReal* position2,const extIkReal* quaternion2,extIkReal* positionOut,extIkReal* quaternionOut);
int simEmbMultiplyMatrices(const extIkReal* matrix1,const extIkReal* matrix2,extIkReal* matrixOut);
int simEmbInterpolateTransformations(const extIkReal* position1,const extIkReal* quaternion1,const extIkReal* position2,const extIkReal* quaternion2,extIkReal interpolFactor,extIkReal* positionOut,extIkReal* quaternionOut);
int simEmbInterpolateMatrices(const extIkReal* matrix1,const extIkReal* matrix2,extIkReal interpolFactor,extIkReal* matrixOut);
int simEmbMultTransformationWithVector(const extIkReal* position,const extIkReal* quaternion,extIkReal* vect);
int simEmbMultMatrixWithVector(const extIkReal* matrix,extIkReal* vect);
int simEmbGetRotationAxis(const extIkReal* positionStart,const extIkReal* quaternionStart,const extIkReal* positionGoal,const extIkReal* quaternionGoal,extIkReal* axis,extIkReal* angle);
int simEmbGetRotationAxis_matrix(const extIkReal* matrixStart,const extIkReal* matrixGoal,extIkReal* axis,extIkReal* angle);
int simEmbRotateAroundAxis(const extIkReal* positionIn,const extIkReal* quaternionIn,const extIkReal* axisVector,const extIkReal* axisPosition,extIkReal angle,extIkReal* positionOut,extIkReal* quaternionOut);
int simEmbRotateAroundAxis_matrix(const extIkReal* matrixIn,const extIkReal* axisVector,const extIkReal* axisPosition,extIkReal angle,extIkReal* matrixOut);
