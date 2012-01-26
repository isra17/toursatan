#include "CClientEventEngine.h"
#include "CClientSession.h"

CClientEventEngine::CClientEventEngine(boost::shared_ptr<CClientSession> session) 
: CEventEngine(), m_session(session), m_sessionThread(&CClientSession::run, m_session)
{
	assert(m_session);
}

Int8 CClientEventEngine::getConnectionID() const
{
	return m_session->id();
}

void CClientEventEngine::setConnectionID(Int8 id)
{
	m_session->setId(id);
}

void CClientEventEngine::newEvent(CEventEngine::EventPtr event)
{
	m_session->send(event);
}