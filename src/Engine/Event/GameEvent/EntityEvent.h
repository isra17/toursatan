#ifndef ENTITYEVENT_H
#define ENTITYEVENT_H

#include "../CEvent.h"
#include "../../Entity/CBaseHandle.h"

//!Détruit une entité
class CEntityKilledEvent
{
public:
	//!unserialize l'objet
	CEntityKilledEvent(std::istringstream& data);

	CEntityKilledEvent(CBaseHandle handle);

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;

private :
	CBaseHandle m_handle;
};

#endif

