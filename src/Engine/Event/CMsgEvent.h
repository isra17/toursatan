#ifndef CMSGEVENT_H
#define CMSGEVENT_H

#include "CEvent.h"
#include "EventID.h"
#include "../Log/CLog.h"
#include <algorithm>

#include "../Entity/IEntity.h"

#include <SFMl/Graphics.hpp>

//!Les event sont des messages envoyer au moteur de jeu
class CMsgEvent : public CEvent
{
public :
	CMsgEvent(std::istringstream& data) : CEvent(EVENT_MSG)
	{
		char buffer[256];
		data.getline(buffer,256);
		m_msg = buffer;
	}

	CMsgEvent(std::string msg)
		: m_msg(msg), CEvent(EVENT_MSG)
	{}

	virtual void apply() const
	{
		CLog::debug(m_msg);
	}

protected :
	virtual void serializeEvent(std::ostringstream& buffer) const
	{
		buffer << m_msg;
	}

private:
	std::string m_msg;
};

#endif