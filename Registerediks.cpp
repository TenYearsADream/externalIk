
#include "Registerediks.h"
#include "ikRoutine.h"
#include "Ct.h"
#include "Tt.h"
#include "v_repConst.h"


CRegisterediks::CRegisterediks()
{
}

CRegisterediks::~CRegisterediks()
{
    removeAllIkGroups();
}

CikGroup* CRegisterediks::getIkGroup(int groupID)
{
     for (int i=0;i<int(ikGroups.size());i++)
     {
        if (ikGroups[i]->getObjectID()==groupID)
            return(ikGroups[i]);
     }
     return(NULL);
}

CikGroup* CRegisterediks::getIkGroup(std::string groupName)
{
    for (int i=0;i<int(ikGroups.size());i++)
    {
        if (ikGroups[i]->getObjectName().compare(groupName)==0)
            return(ikGroups[i]);
    }
    return(NULL);
}

void CRegisterediks::removeIkGroup(int ikGroupID)
{
    Ct::ct->objCont->announceIkGroupWillBeErased(ikGroupID);
    for (int i=0;i<int(ikGroups.size());i++)
    {
        if (ikGroups[i]->getObjectID()==ikGroupID)
        {
            delete ikGroups[i];
            ikGroups.erase(ikGroups.begin()+i);
            return;
        }
    }
}

void CRegisterediks::removeAllIkGroups()
{
    while (ikGroups.size()!=0)
        removeIkGroup(ikGroups[0]->getObjectID());
}

void CRegisterediks::announceObjectWillBeErased(int objID)
{ // Never called from copy buffer!
    int i=0;
    while (i<int(ikGroups.size()))
    {
        if (ikGroups[i]->announceObjectWillBeErased(objID,false))
        { // This ik group has to be erased:
            removeIkGroup(ikGroups[i]->getObjectID()); // This will call announceIkGroupWillBeErased!
            i=0; // order may have changed!
        }
        else
            i++;
    }
}

void CRegisterediks::resetCalculationResults()
{
    for (int i=0;i<int(ikGroups.size());i++)
        ikGroups[i]->resetCalculationResult();
}

void CRegisterediks::announceIkGroupWillBeErased(int ikGroupID)
{ // Never called from copy buffer!
    int i=0;
    while (i<int(ikGroups.size()))
    {
        if (ikGroups[i]->announceIkGroupWillBeErased(ikGroupID,false))
        { // This ik group has to be erased (normally never happens)
            removeIkGroup(ikGroups[i]->getObjectID()); // This will call announceIkGroupWillBeErased!
            i=0; // ordering may have changed!
        }
        else
            i++;
    }
}

int CRegisterediks::computeAllIkGroups(bool exceptExplicitHandling)
{
    int performedCount=0;

    {
        for (int i=0;i<int(ikGroups.size());i++)
        {
            if ((!exceptExplicitHandling)||(!ikGroups[i]->getExplicitHandling()))
            {
                int res=0;
                res=ikGroups[i]->computeGroupIk(false);
                ikGroups[i]->setCalculationResult(res,0);
                if (res!=sim_ikresult_not_performed)
                    performedCount++;
            }
        }
    }
    return(performedCount);
}

void CRegisterediks::addIkGroupExtIk(CikGroup* anIkGroup)
{ // Be careful! We don't check if the group is valid!!
    ikGroups.push_back(anIkGroup);
}
