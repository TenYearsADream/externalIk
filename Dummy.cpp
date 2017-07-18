

#include "v_repConst.h"
#include "Dummy.h"
#include "Ct.h"
#include "Global.h"


CDummy::CDummy()
{
    _objectType=sim_object_dummy_type;
    _objectName="default";

    _linkedDummyID=-1;
    _linkType=sim_dummy_linktype_ik_tip_target;
}

CDummy::~CDummy()
{
}

void CDummy::performObjectLoadingMapping(std::vector<int>* map)
{ // New_Object_ID=map[Old_Object_ID]
    performObjectLoadingMappingMain(map);
    _linkedDummyID=Ct::ct->objCont->getLoadingMapping(map,_linkedDummyID);
}

void CDummy::setLinkedDummyID(int id,bool setDirectly)
{
    int before=_linkedDummyID;
    if (setDirectly)
        _linkedDummyID=id;
    else
    {
        CDummy* linkedDummy=Ct::ct->objCont->getDummy(_linkedDummyID);
        if (id==-1)
        { // we unlink this dummy and its partner:
            if (linkedDummy!=NULL)
                linkedDummy->setLinkedDummyID(-1,true);
            _linkedDummyID=-1;
        }
        else if (_linkedDummyID!=id)
        { // We link this dummy to another dummy
            CDummy* newLinkedDummy=Ct::ct->objCont->getDummy(id);
            if (linkedDummy!=NULL)
                linkedDummy->setLinkedDummyID(-1,true); // we first detach it from its old partner
            if (newLinkedDummy!=NULL)
            { // we detach the new dummy from its original linking:
                newLinkedDummy->setLinkedDummyID(-1,false);
                _linkedDummyID=id;
                newLinkedDummy->setLinkedDummyID(getID(),true);

                if (_linkType==sim_dummy_linktype_gcs_tip)
                    newLinkedDummy->setLinkType(sim_dummy_linktype_gcs_target,true);
                if (_linkType==sim_dummy_linktype_gcs_target)
                    newLinkedDummy->setLinkType(sim_dummy_linktype_gcs_tip,true);
                if ( (_linkType==sim_dummy_linktype_ik_tip_target)||(_linkType==sim_dummy_linktype_gcs_loop_closure)||(_linkType==sim_dummy_linktype_dynamics_loop_closure)||(_linkType==sim_dummy_linktype_dynamics_force_constraint) )
                    newLinkedDummy->setLinkType(_linkType,true);
            }
            else
                _linkedDummyID=-1; // that dummy doesn't exist
        }
    }
    if (before!=_linkedDummyID)
    {
    }
}

void CDummy::setLinkType(int lt,bool setDirectly)
{
    _linkType=lt;
    if ((_linkedDummyID!=-1)&&(!setDirectly))
    {
        CDummy* it=Ct::ct->objCont->getDummy(_linkedDummyID);
        if (it!=NULL)
        {
            if (lt==sim_dummy_linktype_gcs_tip)
                it->setLinkType(sim_dummy_linktype_gcs_target,true);
            if (lt==sim_dummy_linktype_gcs_target)
                it->setLinkType(sim_dummy_linktype_gcs_tip,true);
            if ( (lt==sim_dummy_linktype_ik_tip_target)||(lt==sim_dummy_linktype_gcs_loop_closure)||(lt==sim_dummy_linktype_dynamics_loop_closure)||(lt==sim_dummy_linktype_dynamics_force_constraint) )
                it->setLinkType(lt,true);
        }
    }
}

C7Vector CDummy::getTempLocalTransformation()
{
    return(_localTransformation_temp);
}

void CDummy::setTempLocalTransformation(const C7Vector& tr)
{
    _localTransformation_temp=tr;
}

int CDummy::getLinkType()
{
    return(_linkType);
}


int CDummy::getLinkedDummyID()
{
    return(_linkedDummyID);
}

bool CDummy::announceObjectWillBeErased(int objID,bool copyBuffer)
{   // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    // This routine can be called for objCont-objects, but also for objects
    // in the copy-buffer!! So never make use of any 
    // 'Ct::ct->objCont->getObject(id)'-call or similar
    // Return value true means 'this' has to be erased too!
    announceObjectWillBeErasedMain(objID,copyBuffer);
    if (_linkedDummyID==objID)
        setLinkedDummyID(-1,copyBuffer);
    return(false);
}

void CDummy::announceIkObjectWillBeErased(int ikGroupID,bool copyBuffer)
{   // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    announceIkObjectWillBeErasedMain(ikGroupID,copyBuffer);
}

void CDummy::serializeRExtIk(CExtIkSer& ar)
{ 
    serializeRExtIkMain(ar);

    _linkedDummyID=ar.readInt();

    _linkType=ar.readInt();
}
