#include "CServerEventEngine.h"
#include "CServerSession.h"
#include "CServerClientSession.h"

CServerEventEngine::CServerEventEngine(boost::shared_ptr<CServerSession> session)
: CEventEngine(), m_session(session), m_sessionThread(&CServerSession::run, m_session)
{

}

Int8 CServerEventEngine::getConnectionID() const
{
	return -1;
}

void CServerEventEngine::handleEvent(CEventEngine::EventPtr event)
{
	if(event->onSend())
	{
		m_session->send(event);
		CEventEngine::handleEvent(event);
	}
}

void CServerEventEngine::newEvent(CEventEngine::EventPtr event)
{
	pushEvent(event);
}


void CServerEventEngine::setClientState(UInt8 playerID, UInt8 stateID)
{
	m_session->setClientState(playerID, static_cast<ClientState>(stateID));
}