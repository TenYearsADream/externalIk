#pragma once

#include "extIk.h"
#include "3DObject.h"
#include "jointObject.h"
#include "ikGroup.h"
#include "MainCont.h"

class CObjCont : public CMainCont 
{
public:
    CObjCont();
    virtual ~CObjCont();

public:
    void newSceneProcedure();
    void removeAllObjects();
    void actualizeObjectInformation();

    int getLoadingMapping(std::vector<int>* map,int oldVal);

    int getObjectIdentifier(const std::string& objectName);
    C3DObject* getObject(int identifier);
    CDummy* getDummy(int identifier);
    CJoint* getJoint(int identifier);
    C3DObject* getObject(const std::string& name);

    bool makeObjectChildOf(C3DObject* childObject,C3DObject* parentObject);
    void setAbsoluteConfiguration(int identifier,const C7Vector& v,bool keepChildrenInPlace);

    int getHighestObjectID();
    bool eraseObject(C3DObject* it);

    void announceObjectWillBeErased(int objectID);
    void announceIkGroupWillBeErased(int ikGroupID);

    std::vector<int> objectsWhichNeedToBeErased;
    void enableObjectActualization(bool e);

    std::vector<C3DObject*> _objectIndex;

    bool _objectActualizationEnabled;

    int _nextObjectHandle;

    std::vector<int> orphanList;
    std::vector<int> objectList;
    std::vector<int> jointList;
    std::vector<int> dummyList;

    void importIkContent(CExtIkSer& ar);
    bool addObjectToSceneExtIk(C3DObject* newObject);
};

