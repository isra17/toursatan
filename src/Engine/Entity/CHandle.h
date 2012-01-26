#ifndef CHANDLE_H
#define CHANDLE_H

#include "CBaseHandle.h"
#include "../CGameEngine.h"

//!Rajout d'une fonction de cast a CBaseHandle
class CHandle : public CBaseHandle
{
    public:
        CHandle() : CBaseHandle(){}

        CHandle(const unsigned int& index, const unsigned int& serial)
            : CBaseHandle(index,serial){}

        CHandle(const CBaseHandle& hHandle) : CBaseHandle(hHandle){}

		//!Recherche le handle dans la liste de d'entity et downcast au type demandé
        template<class DownClass> boost::shared_ptr<DownClass> to() const
        {
			return boost::shared_dynamic_cast<DownClass>(CGameEngine::instance()->findEntity(*this));
        }
    private:

};

#endif

