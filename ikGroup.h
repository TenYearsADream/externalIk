
#pragma once

#include "extIk.h"
#include "ikEl.h"
#include "3DObject.h"
#include "jointObject.h"
#include "Dummy.h"

class CikGroup  
{
public:
    CikGroup();
    virtual ~CikGroup();

public:
    bool announceObjectWillBeErased(int objID,bool copyBuffer);
    bool announceIkGroupWillBeErased(int ikGroupID,bool copyBuffer);
    void performObjectLoadingMapping(std::vector<int>* map);

    CikEl* getIkElement(int ikElementID);
    CikEl* getIkElementWithTooltipID(int tooltipID);
    void removeIkElement(int elementID);

    void setExplicitHandling(bool explicitHandl);
    bool getExplicitHandling();
    void setAllInvolvedJointsToPassiveMode();

    int getObjectID();
    std::string getObjectName();
    void setObjectName(std::string newName);
    void setMaxIterations(int maxIter);
    int getMaxIterations();
    bool getActive();
    void setDlsFactor(extIkReal theFactor);
    extIkReal getDlsFactor();
    void setCalculationMethod(int theMethod);
    int getCalculationMethod();
    bool getRestoreIfPositionNotReached();
    bool getRestoreIfOrientationNotReached();

    int getDoOnFailOrSuccessOf();
    bool getDoOnFail();
    bool getDoOnPerformed();
    void setConstraints(int constr);
    int getConstraints();
    void setJointLimitWeight(extIkReal weight);
    extIkReal getJointLimitWeight();

    extIkReal getJointTreshholdAngular();
    extIkReal getJointTreshholdLinear();
    int computeGroupIk(bool forMotionPlanning);
    void getAllActiveJoints(std::vector<CJoint*>& jointList);
    void getTipAndTargetLists(std::vector<CDummy*>& tipList,std::vector<CDummy*>& targetList);

    bool getIgnoreMaxStepSizes();
    void resetCalculationResult();
    void setCalculationResult(int res,int calcTimeInMs);
    int getCalculationResult();
    void setCorrectJointLimits(bool c);
    bool getCorrectJointLimits();

    void setActive(bool isActive);

    extIkReal* getLastJacobianData(int matrixSize[2]);
    extIkReal* getLastManipulabilityValue(int matrixSize[2]);
    extIkReal getDeterminant(const CMatrix& m,const std::vector<int>* activeRows,const std::vector<int>* activeColumns);

    // Variables which need to be serialized and copied:
    std::vector<CikEl*> ikElements;

private:
    void _resetTemporaryParameters();
    void _applyTemporaryParameters();

    int performOnePass(std::vector<CikEl*>* validElements,bool& limitOrAvoidanceNeedMoreCalculation,extIkReal interpolFact,bool forMotionPlanning);

    // Variables which need to be serialized and copied:
    int objectID;
    std::string objectName;
    int maxIterations;
    bool active;
    bool _correctJointLimits;
    extIkReal dlsFactor;
    int calculationMethod;
    bool restoreIfPositionNotReached;
    bool restoreIfOrientationNotReached;
    int doOnFailOrSuccessOf; // group identifier which success/fail will be evaluated
    bool doOnFail;
    bool doOnPerformed;
    int constraints; // only sim_avoidance_constraint is valid!
    extIkReal jointLimitWeight;
    extIkReal jointTreshholdAngular;    // in radian
    extIkReal jointTreshholdLinear;     // in meter

    bool ignoreMaxStepSizes;
    int _calculationResult;

    CMatrix* _lastJacobian;

    bool _explicitHandling;

public:
    void serializeRExtIk(CExtIkSer& ar);
};
