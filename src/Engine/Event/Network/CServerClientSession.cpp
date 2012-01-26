#include "CServerClientSession.h"
#include "CServerSession.h"
#include <iostream>

#include "../CEventFactory.h"
#include "../CEventEngine.h"
#include "../GameEvent/NetworkEvent.h"

#include "../../Log/CLog.h"

CServerClientSession::CServerClientSession(CConnection_ptr connection, Int8 id, CServerSession& server)
: m_connection(connection), m_id(id), m_server(server), m_state(NOTREADY)
{
}

boost::asio::ip::tcp::socket& CServerClientSession::socket()
{
	return m_connection->socket();
}

void CServerClientSession::start()
{
	m_connection->socket().set_option(boost::asio::ip::tcp::no_delay(true));

	//Envoie l'event Hello pour bien commencer la session
	boost::shared_ptr<CNetworkHelloEvent> helloEvent(new CNetworkHelloEvent(id()));
	send(helloEvent);

	m_connection->asyncRead(m_readBuffer,
		boost::bind(
			&CServerClientSession::handleRead, this,
			boost::asio::placeholders::error));
}

void CServerClientSession::close()
{
	m_connection.reset();
}

void CServerClientSession::send(boost::shared_ptr<CEvent> event)
{
	const std::string& binEvent(event->serialize());

	bool write_in_progress = !m_sendBuffers.empty();
	m_sendBuffers.push(binEvent);
	if (!write_in_progress)
	{
		m_connection->asyncWrite(m_sendBuffers.front(),
			boost::bind(&CServerClientSession::handleSend, this,
				boost::asio::placeholders::error));
	}
}

Int8 CServerClientSession::id()
{
	return m_id;
}

void CServerClientSession::handleSend(const boost::system::error_code& error)
{
	if (!error)
	{
		m_sendBuffers.pop();
		if (!m_sendBuffers.empty())
		{
			m_connection->asyncWrite(m_sendBuffers.front(),
				boost::bind(&CServerClientSession::handleSend, this,
					boost::asio::placeholders::error));
		}
	}
	else
	{
		//Impossible d'envoyer au serveur
		throw(std::runtime_error(error.message()));
		m_server.close(m_id);
	}
}


void CServerClientSession::handleRead(const boost::system::error_code& error)
{
	if (!error)
	{
		UInt16 eventID = *((UInt16*)m_readBuffer.c_str());
		boost::shared_ptr<CEvent> event = CEventFactory::build(eventID,m_readBuffer);
		event->setSource(m_id);
		CGameEngine::instance()->getEventEngine()->newEvent(event);

		m_connection->asyncRead(m_readBuffer,
		boost::bind(
			&CServerClientSession::handleRead, this,
			boost::asio::placeholders::error));
	}
	else
	{
		throw(std::runtime_error(error.message()));
		m_server.close(m_id);
	}
}

void CServerClientSession::setState(ClientState state)
{
	m_state = state;
}

ClientState CServerClientSession::getState()
{
	return m_state;
}