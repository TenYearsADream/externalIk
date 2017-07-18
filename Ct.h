
#pragma once

#include "extIk.h"
#include "Registerediks.h"
#include "ObjCont.h"

class Ct  
{
public:
    Ct();
    virtual ~Ct();
    void createSingletonsAndOneInstance();
    void destroySingletonsAndAllInstances();

public:
    void emptyScene(bool notCalledFromUndoFunction);
    int createNewInstance(bool triggerCallbackAndHandleDialogs);
    bool makeInstanceCurrentFromIndex(int instanceIndex,bool triggerCallbackAndHandleDialogs);
    int destroyCurrentInstance();

private:    
    int currentInstanceIndex;

    static std::vector<Ct*> _allCts;
    static std::vector<int> _allCtHandles;
    static int _nextHandle;

public:
    CRegisterediks* ikGroups;
    CObjCont* objCont;

    std::vector<CRegisterediks*> ikGroupList;
    std::vector<CObjCont*> objContList;

    static Ct* ct;
    static int currentHandle;

    static int insertNewInstance(Ct* inst);
    static int removeInstance(int handle);
    static bool switchToInstance(int handle);
};

