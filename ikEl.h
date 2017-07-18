
#pragma once

#include "extIk.h"
#include "extIkSer.h"
#include "MyMath.h"

class CikEl  
{
public:
    CikEl();
    CikEl(int theTooltip);
    virtual ~CikEl();

public:
    void commonInit();
    bool announceObjectWillBeErased(int objID,bool copyBuffer);
    void performObjectLoadingMapping(std::vector<int>* map);
    int getObjectID();
    int getTooltip();
    int getBase();
    void setAllInvolvedJointsToPassiveMode();
    bool getActive();
    void setActive(bool isActive);
    void setBase(int newBase);
    int getAlternativeBaseForConstraints(); 
    int getTarget();
    extIkReal getMinAngularPrecision();
    extIkReal getMinLinearPrecision();
    void setMinAngularPrecision(extIkReal prec);
    void setMinLinearPrecision(extIkReal prec);
    void setConstraints(int constr);
    int getConstraints();
    void setPositionWeight(extIkReal weight);
    extIkReal getPositionWeight();
    void setOrientationWeight(extIkReal weight);
    extIkReal getOrientationWeight();

    void checkIfWithinTolerance(bool& position,bool& orientation,bool useTempValues);
    void prepareIkEquations(extIkReal interpolFact);
    void removeIkEquations();
    void getError(const C4X4Matrix& m1,const C4X4Matrix& m2,extIkReal err[2],bool xC,bool yC,bool zC,bool abC,bool gC);

    // various:
    CMatrix* matrix;
    CMatrix* matrix_correctJacobian;
    CMatrix* errorVector;
    std::vector<int>* rowJointIDs;
    std::vector<int>* rowJointStages;

private:
    // Variables which need to be serialized and copied:
    int objectID;
    int tooltip;
    int base;
    int alternativeBaseForConstraints;
    extIkReal minAngularPrecision;
    extIkReal minLinearPrecision;
    bool active;
    int constraints; // Bit-coded: use sim_x_constraint, etc. values!
                    // sim_avoidance_conjstraint is reserved for collections! Don't use it here!!
    extIkReal positionWeight;
    extIkReal orientationWeight;

public:
    void serializeRExtIk(CExtIkSer& ar);
};
