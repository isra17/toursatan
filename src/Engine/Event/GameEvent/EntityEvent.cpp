#include "EntityEvent.h"
#include "../../Entity/IEntity.h"

//unserialize l'objet
CEntityKilledEvent::CEntityKilledEvent(std::istringstream& data)
{
	UInt8 handle;
	data.read((char*)&handle, sizeof(UInt32));
	m_handle = handle;
}

CEntityKilledEvent::CEntityKilledEvent(CBaseHandle handle)
{
	m_handle = handle;
}

void CEntityKilledEvent::apply() const
{
	CHandle handle(m_handle);
	handle.to<IEntity>()->doDie();
}

//serialize l'objet
void CEntityKilledEvent::serializeEvent(std::ostringstream& buffer) const
{
	UInt32 handle = m_handle;
	buffer.write((char*)&handle, sizeof(UInt32));
}

