
#pragma once

#include "extIk.h"
#include "MyMath.h"
#include "jointObject.h"
#include "Dummy.h"
#include "ikEl.h"
#include "ikGroup.h"

class CIkRoutine  
{
public:
    static void multiply(C4X4FullMatrix& d0,C4X4FullMatrix& dp,int index,std::vector<C4X4FullMatrix*>& allMatrices);
    static void buildDeltaZRotation(C4X4FullMatrix& d0,C4X4FullMatrix& dp,extIkReal screwCoeff);
    static void buildDeltaZTranslation(C4X4FullMatrix& d0,C4X4FullMatrix& dp);
    static CMatrix* getJacobian(CikEl* ikElement,C4X4Matrix& tooltipTransf,std::vector<int>* rowJointIDs=NULL,std::vector<int>* rowJointStages=NULL);
    static void performGroupIK(CikGroup* ikGroup);
};
