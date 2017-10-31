#pragma once

#include "extIk.h"
#include "3DObject.h"
#include "3Vector.h"
#include "7Vector.h"
#include <vector>
#include <string>

class CDummy : public C3DObject  
{
public:

    CDummy();
    virtual ~CDummy();

public:
    bool announceObjectWillBeErased(int objID,bool copyBuffer);
    void announceIkObjectWillBeErased(int ikGroupID,bool copyBuffer);

    void performObjectLoadingMapping(std::vector<int>* map);

    void setLinkedDummyID(int id,bool setDirectly);
    void setLinkType(int lt,bool setDirectly);
    int getLinkedDummyID();
    int getLinkType();

    C7Vector getTempLocalTransformation();
    void setTempLocalTransformation(const C7Vector& tr);

protected:
    C7Vector _localTransformation_temp; // used for IK (needed when the dummy is freely sliding on a path object!)

    // Variables which need to be serialized & copied 
    int _linkedDummyID;
    int _linkType;

public:
    void serializeRExtIk(CExtIkSer& ar);
};
