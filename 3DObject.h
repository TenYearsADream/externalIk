
#pragma once

#include "extIk.h"
#include "MyMath.h"
#include "extIkSer.h"
#include "3Vector.h"
#include "4Vector.h"
#include "7Vector.h"

class C3DObject  
{
public:

    C3DObject();
    virtual ~C3DObject();

public:
    virtual bool announceObjectWillBeErased(int objID,bool copyBuffer);
    virtual void announceIkObjectWillBeErased(int ikGroupID,bool copyBuffer);

    void announceObjectWillBeErasedMain(int objID,bool copyBuffer);
    void announceIkObjectWillBeErasedMain(int ikGroupID,bool copyBuffer);

    virtual void performObjectLoadingMapping(std::vector<int>* map);
    void performObjectLoadingMappingMain(std::vector<int>* map);

    void getCumulativeTransformationMatrix(extIkReal m[4][4],bool useTempValues=false);
    void getCumulativeTransformationMatrixPart1(extIkReal m[4][4],bool useTempValues=false);

    void setLocalTransformation(const C7Vector& v);
    void setLocalTransformation(const C4Vector& q);
    void setLocalTransformation(const C3Vector& x);

    void setAbsoluteTransformation(const C7Vector& v);
    void setAbsoluteTransformation(const C4Vector& q);
    void setAbsoluteTransformation(const C3Vector& x);
    C7Vector getParentCumulativeTransformation(bool useTempValues=false);
    C7Vector getCumulativeTransformation(bool useTempValues=false);
    C7Vector getLocalTransformation(bool useTempValues=false);
    C7Vector getCumulativeTransformationPart1(bool useTempValues=false);
    C7Vector& getLocalTransformationPart1(bool useTempValues=false); 

    int getID();
    void setID(int newID);
    void setName(std::string newName);
    std::string getName();
    C3DObject* getParent();
    bool isObjectParentedWith(C3DObject* thePotentialParent);
    int getParentIdentifierLoading();
    void setParentIdentifierLoading(int pID);
    void setParent(C3DObject* newParent,bool actualizeInfo=true);
    int getObjectType();

    std::vector<C3DObject*> childList;

protected:
    C7Vector _transformation; // Quaternion and position
    int _objectID;
    std::string _objectName;
    C3DObject* _parentObject; 
    int _parentID;
    int _objectType;

public:
    virtual void serializeRExtIk(CExtIkSer& ar);
    void serializeRExtIkMain(CExtIkSer& ar);
};
