#pragma once

#include "extIk.h"
#include <vector>
#include "ikGroup.h"
#include "MainCont.h"

class CRegisterediks : public CMainCont 
{
public:
    CRegisterediks();
    virtual ~CRegisterediks();

public:
    CikGroup* getIkGroup(int groupID);
    CikGroup* getIkGroup(std::string groupName);
    void removeIkGroup(int ikGroupID);
    void removeAllIkGroups();
    void announceObjectWillBeErased(int objID);
    void announceIkGroupWillBeErased(int ikGroupID);
    int computeAllIkGroups(bool exceptExplicitHandling);
    void resetCalculationResults();

    // Variable that need to be serialized on an individual basis:
    std::vector<CikGroup*> ikGroups;

public:
    void addIkGroupExtIk(CikGroup* anIkGroup);
};
