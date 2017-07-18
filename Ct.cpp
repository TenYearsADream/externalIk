
#include "Ct.h"

std::vector<Ct*> Ct::_allCts;
std::vector<int> Ct::_allCtHandles;
Ct* Ct::ct=NULL;
int Ct::currentHandle=0;
int Ct::_nextHandle=1;

int Ct::insertNewInstance(Ct* inst)
{
    _allCts.push_back(inst);
    _allCtHandles.push_back(_nextHandle);
    ct=inst;
    currentHandle=_nextHandle;
    _nextHandle++;
    return(_nextHandle-1);
}

int Ct::removeInstance(int handle)
{
    for (int i=0;i<int(_allCtHandles.size());i++)
    {
        if (_allCtHandles[i]==handle)
        {
            _allCtHandles.erase(_allCtHandles.begin()+i);
            _allCts.erase(_allCts.begin()+i);
            if (currentHandle==handle)
            {
                currentHandle=0;
                ct=NULL;
                if (_allCtHandles.size()>0)
                {
                    currentHandle=_allCtHandles[0];
                    ct=_allCts[0];
                }
                return(currentHandle);
            }
        }
    }
    return(-1); // error, instance doesn't exist
}

bool Ct::switchToInstance(int handle)
{
    for (int i=0;i<int(_allCtHandles.size());i++)
    {
        if (_allCtHandles[i]==handle)
        {
            currentHandle=handle;
            ct=_allCts[i];
            return(true);
        }
    }
    return(false); // error, instance doesn't exist
}

Ct::Ct()
{
    currentInstanceIndex=-1;
    ikGroups=NULL;
    objCont=NULL;
    createSingletonsAndOneInstance(); // This has to be done at the very beginning!
}

Ct::~Ct()
{
    destroySingletonsAndAllInstances(); // This has to be done at the very end
}

int Ct::createNewInstance(bool triggerCallbackAndHandleDialogs)
{
    ikGroupList.push_back(NULL);
    objContList.push_back(NULL);

    currentInstanceIndex=int(objContList.size())-1;


    ikGroups=NULL;
    objCont=NULL;

    ikGroups=new CRegisterediks();
    objCont=new CObjCont();


    ikGroupList[currentInstanceIndex]=ikGroups;
    objContList[currentInstanceIndex]=objCont;


    return(currentInstanceIndex);
}

int Ct::destroyCurrentInstance()
{
    if (currentInstanceIndex==-1)
        return(-1);


    // Important to empty objects first (since ct::objCont->announce....willBeErase
    // might be called for already destroyed objects!)

    ikGroups->removeAllIkGroups();


    objCont->removeAllObjects();




    delete objCont;
    objCont=NULL;


    delete ikGroups;
    ikGroups=NULL;



    objContList.erase(objContList.begin()+currentInstanceIndex);
    ikGroupList.erase(ikGroupList.begin()+currentInstanceIndex);

    if (objContList.size()!=0)
    {
        currentInstanceIndex=-1; // We set this so that next instruction succeeds (otherwise we might already be in instance 0 and the function will not process). Added on 5/3/2012
        makeInstanceCurrentFromIndex(int(objContList.size())-1,true);
    }
    else
        currentInstanceIndex=-1;
    return(currentInstanceIndex);   
}

void Ct::createSingletonsAndOneInstance()
{
    createNewInstance(true);
}

void Ct::destroySingletonsAndAllInstances()
{

    while (objContList.size()!=0)
    {
        makeInstanceCurrentFromIndex(int(objContList.size())-1,true);
        destroyCurrentInstance();
    }

}

void Ct::emptyScene(bool notCalledFromUndoFunction)
{

    // Following is saved:

    ikGroups->removeAllIkGroups();


    objCont->newSceneProcedure();

}

bool Ct::makeInstanceCurrentFromIndex(int instanceIndex,bool triggerCallbackAndHandleDialogs)
{ 
    if ( (instanceIndex<0)||(instanceIndex>=int(objContList.size())))
        return(false);

    if (currentInstanceIndex==instanceIndex)
        return(true);

    currentInstanceIndex=instanceIndex;

    ikGroups=ikGroupList[currentInstanceIndex];
    objCont=objContList[currentInstanceIndex];


    return(true);
}
