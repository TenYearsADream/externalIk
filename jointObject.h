
#pragma once

#include "extIk.h"
#include "3DObject.h"

class CJoint : public C3DObject  
{
public:
    CJoint(); // default, use only during serialization!
    CJoint(int jointType);
    virtual ~CJoint();

public:
    void commonInit();

    bool announceObjectWillBeErased(int objID,bool copyBuffer);
    void announceIkObjectWillBeErased(int ikGroupID,bool copyBuffer);

    void performObjectLoadingMapping(std::vector<int>* map);

    extIkReal getPosition(bool useTempValues=false);
    void setPosition(extIkReal parameter,bool useTempValues=false);
    extIkReal getPosition_ratio();
    void setPosition_ratio(extIkReal posRatio);

    void initializeParametersForIK(extIkReal angularJointLimitationThreshold);
    int getDoFs();
    void getLocalTransformationExPart1(C7Vector& mTr,int index,bool useTempValues=false);
    extIkReal getTempParameterEx(int index);
    void setTempParameterEx(extIkReal parameter,int index);
    void applyTempParametersEx();
    int getTempSphericalJointLimitations();

    extIkReal getScrewPitch() const;
    void setSphericalTransformation(const C4Vector& tr);
    C4Vector getSphericalTransformation() const;
    int getJointType();
    extIkReal getPositionIntervalMin();
    void setPositionIntervalMin(extIkReal m);
    extIkReal getPositionIntervalRange();
    void setPositionIntervalRange(extIkReal r);

    bool getPositionIsCyclic();
    void setPositionIsCyclic(bool c);

    extIkReal getIKWeight();
    void setIKWeight(extIkReal newWeight);
    void setMaxStepSize(extIkReal stepS);
    extIkReal getMaxStepSize(); 

    void _rectifyDependentJoints();

    void setJointMode(int theMode);
    int getJointMode();
    int getDependencyJointID();
    extIkReal getDependencyJointCoeff();
    extIkReal getDependencyJointFact();

    // Various
    std::vector<CJoint*> directDependentJoints;

protected:
    // Variables which need to be serialized & copied
    // Main joint attributes:
    int _jointType;
    C4Vector _sphericalTransformation;
    bool _positionIsCyclic;
    extIkReal _screwPitch;
    extIkReal _jointMinPosition;
    extIkReal _jointPositionRange;

    // Joint state and other:
    extIkReal _jointPosition;

    // IK and path planning calculation:
    extIkReal _maxStepSize;

    // General IK calculation:
    extIkReal _ikWeight;

    int _jointMode;
    int _dependencyJointID;
    extIkReal _dependencyJointCoeff;
    extIkReal _dependencyJointFact;

    // Temporary values used when doing IK:
    extIkReal _jointPosition_tempForIK;
    extIkReal _sphericalTransformation_euler1TempForIK;
    extIkReal _sphericalTransformation_euler2TempForIK;
    extIkReal _sphericalTransformation_euler3TempForIK;
    int _sphericalTransformation_eulerLockTempForIK; // bit-coded, bit0--> _sphericalTransformation_euler1TempForIK, bit1--> _sphericalTransformation_euler2TempForIK, etc.

public:
    void serializeRExtIk(CExtIkSer& ar);
};
