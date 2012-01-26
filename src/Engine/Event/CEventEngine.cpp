#include "CEventEngine.h"

#include "../Log/CLog.h"

boost::mutex CEventEngine::m_evMutex;

CEventEngine::CEventEngine()
{

}

void CEventEngine::newEvent(CEventEngine::EventPtr event)
{
	pushEvent(event);
}

void CEventEngine::handleEvent(CEventEngine::EventPtr event)
{
	//Applique l'event avec le contexte du jeu courant
	event->apply();
}

//Thread safe
void CEventEngine::pushEvent(CEventEngine::EventPtr event)
{
	//Lock la queue d'events
	boost::mutex::scoped_lock lock(m_evMutex);
	//Ajoute l'event a la queue
	m_events.push(event);
}



void CEventEngine::onFrame(float m_lastFrame)
{
	//Lock la queue d'events
	boost::mutex::scoped_lock lock(m_evMutex);
	//Traite et vide la queue d'event
	while(!m_events.empty())
	{
		handleEvent(m_events.front());
		m_events.pop();
	}
}
