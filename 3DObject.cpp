
#include "v_repConst.h"
#include "jointObject.h"
#include "3DObject.h"
#include "Dummy.h"
#include "Ct.h"
#include "Global.h"

C3DObject::C3DObject()
{
    _parentObject=NULL;
    _parentID=-1;
    _objectID=0;
    _transformation.setIdentity();
}

C3DObject::~C3DObject() 
{
}

void C3DObject::performObjectLoadingMapping(std::vector<int>* map)
{
}

void C3DObject::performObjectLoadingMappingMain(std::vector<int>* map)
{
    int newParentID=Ct::ct->objCont->getLoadingMapping(map,_parentID);
    setParent(Ct::ct->objCont->getObject(newParentID));
}

std::string C3DObject::getName()
{
    return(_objectName);
}
void C3DObject::setName(std::string newName)
{ 
    _objectName=newName;
}

bool C3DObject::announceObjectWillBeErased(int objID,bool copyBuffer)
{
    return(false);
}
void C3DObject::announceIkObjectWillBeErased(int ikGroupID,bool copyBuffer)
{
}

void C3DObject::announceObjectWillBeErasedMain(int objID,bool copyBuffer)
{ 
    if ( (getParent()!=NULL)&&(!copyBuffer) )
    {
        if (getParent()->getID()==objID)
            Ct::ct->objCont->makeObjectChildOf(this,getParent()->getParent());
    }
}
void C3DObject::announceIkObjectWillBeErasedMain(int ikGroupID,bool copyBuffer)
{
}

void C3DObject::getCumulativeTransformationMatrix(extIkReal m[4][4],bool useTempValues) 
{ // useTempValues is false by default. This is used by the IK-routine
    getCumulativeTransformation(useTempValues).copyTo(m);
}

void C3DObject::getCumulativeTransformationMatrixPart1(extIkReal m[4][4],bool useTempValues) 
{ // useTempValues is false by default. This is used by the IK-routine
    getCumulativeTransformationPart1(useTempValues).copyTo(m);
}

C7Vector C3DObject::getParentCumulativeTransformation(bool useTempValues)
{ // useTempValues is false by default. This is used by the IK-routine
    if (getParent()==NULL)
    {
        C7Vector retV;
        retV.setIdentity();
        return(retV);
    }
    else
        return(getParent()->getCumulativeTransformation(useTempValues));
}
C7Vector C3DObject::getCumulativeTransformation(bool useTempValues)
{ // useTempValues is false by default. This is used by the IK-routine
    if (getParent()==NULL)
        return(getLocalTransformation(useTempValues));
    else
        return(getParentCumulativeTransformation(useTempValues)*getLocalTransformation(useTempValues));
}
C7Vector C3DObject::getLocalTransformation(bool useTempValues)
{ // useTempValues is false by default. This is used by the IK-routine
    if (getObjectType()==sim_object_joint_type)
    {
        CJoint* it=(CJoint*)this;
        C7Vector jointTr;
        jointTr.setIdentity();
        extIkReal val;
        val=it->getPosition(useTempValues);
        if (it->getJointType()==sim_joint_revolute_subtype)
        {
            jointTr.Q.setAngleAndAxis(val,C3Vector(0.0,0.0,1.0));
            jointTr.X(2)=val*it->getScrewPitch();
        }
        if (it->getJointType()==sim_joint_prismatic_subtype)
            jointTr.X(2)=val;
        if (it->getJointType()==sim_joint_spherical_subtype)
        {
            if (useTempValues)
            {
                if (it->getTempSphericalJointLimitations()==0)
                { // Used by the IK routine when away from joint limitations
                    jointTr.Q.setEulerAngles(0.0,0.0,it->getTempParameterEx(2));
                    C4Vector q2;
                    q2.setEulerAngles(piValD2,0.0,0.0);
                    jointTr.Q=q2*jointTr.Q;

                    q2.setEulerAngles(0.0,0.0,it->getTempParameterEx(1));
                    jointTr.Q=q2*jointTr.Q;
                    q2.setEulerAngles(-piValD2,0.0,-piValD2);
                    jointTr.Q=q2*jointTr.Q;

                    q2.setEulerAngles(0.0,0.0,it->getTempParameterEx(0));
                    jointTr.Q=q2*jointTr.Q;
                    q2.setEulerAngles(0.0,piValD2,0.0);
                    jointTr.Q=q2*jointTr.Q;
                    q2=it->getSphericalTransformation();
                    jointTr.Q=q2*jointTr.Q;
                }
                else
                { // Used by the IK routine when close to joint limitations
                    jointTr.Q.setEulerAngles(0.0,0.0,it->getTempParameterEx(2));
                    C4Vector q2;
                    q2.setEulerAngles(0.0,-piValD2,0.0);
                    jointTr.Q=q2*jointTr.Q;

                    q2.setEulerAngles(0.0,0.0,it->getTempParameterEx(1));
                    jointTr.Q=q2*jointTr.Q;
                    q2.setEulerAngles(0.0,piValD2,0.0);
                    jointTr.Q=q2*jointTr.Q;

                    q2.setEulerAngles(0.0,0.0,it->getTempParameterEx(0));
                    jointTr.Q=q2*jointTr.Q;
                }
            }
            else
                jointTr.Q=it->getSphericalTransformation();
        }
        return(_transformation*jointTr);
    }
    else if (getObjectType()==sim_object_dummy_type)
    {
        CDummy* it=(CDummy*)this;
        if (useTempValues)
            return(it->getTempLocalTransformation()); // used for IK when dummy is freely sliding on a path object
        return(_transformation);
    }
    else
        return(_transformation);
}

C7Vector C3DObject::getCumulativeTransformationPart1(bool useTempValues)
{ // useTempValues is false by default. This is used by the IK-routine
    if (getObjectType()==sim_object_joint_type)
    {
        if (getParent()==NULL)
            return(getLocalTransformationPart1(useTempValues));
        else
            return(getParentCumulativeTransformation(useTempValues)*getLocalTransformationPart1(useTempValues));
    }
    else
        return(getCumulativeTransformation(useTempValues));
}

C7Vector& C3DObject::getLocalTransformationPart1(bool useTempValues)
{ // useTempValues is false by default. This is used by the IK-routine
    return(_transformation);
}

void C3DObject::setLocalTransformation(const C7Vector& v)
{
    _transformation=v;
}

void C3DObject::setLocalTransformation(const C4Vector& q)
{
    _transformation.Q=q;
}
void C3DObject::setLocalTransformation(const C3Vector& x)
{
    _transformation.X=x;
}
void C3DObject::setAbsoluteTransformation(const C7Vector& v)
{
    C7Vector pInv(getParentCumulativeTransformation().getInverse());
    _transformation.setMultResult(pInv,v);
}
void C3DObject::setAbsoluteTransformation(const C4Vector& q)
{
    C7Vector pInv(getParentCumulativeTransformation().getInverse());
    _transformation.Q=pInv.Q*q;
}
void C3DObject::setAbsoluteTransformation(const C3Vector& x)
{
    C7Vector pInv(getParentCumulativeTransformation().getInverse());
    _transformation.X=pInv*x;
}

int C3DObject::getID()
{
    return(_objectID);
}
void C3DObject::setID(int newID)
{ // Be very careful with this function!!!
    _objectID=newID;
}

bool C3DObject::isObjectParentedWith(C3DObject* thePotentialParent)
{
    if (getParent()==NULL)
        return(false);
    if (getParent()==thePotentialParent) 
        return(true);
    return(getParent()->isObjectParentedWith(thePotentialParent));
}

int C3DObject::getParentIdentifierLoading()
{
    return(_parentID);
}

void C3DObject::setParentIdentifierLoading(int pID)
{ // Be very careful with this function!!!
    _parentID=pID;
}

void C3DObject::setParent(C3DObject* newParent,bool actualizeInfo)
{ // actualizeInfo is true by default
    if (newParent==this)
        return;
    _parentObject=newParent;
    if (actualizeInfo) 
        Ct::ct->objCont->actualizeObjectInformation();
}

C3DObject* C3DObject::getParent()
{
    return(_parentObject);
}

int C3DObject::getObjectType()
{
    return(_objectType);
}

void C3DObject::serializeRExtIk(CExtIkSer& ar)
{
}

void C3DObject::serializeRExtIkMain(CExtIkSer& ar)
{
    _transformation.Q(0)=(extIkReal)ar.readFloat();
    _transformation.Q(1)=(extIkReal)ar.readFloat();
    _transformation.Q(2)=(extIkReal)ar.readFloat();
    _transformation.Q(3)=(extIkReal)ar.readFloat();
    _transformation.X(0)=(extIkReal)ar.readFloat();
    _transformation.X(1)=(extIkReal)ar.readFloat();
    _transformation.X(2)=(extIkReal)ar.readFloat();
    
    _objectID=ar.readInt();
    _parentID=ar.readInt();

    _objectName=ar.readString().c_str();
}
