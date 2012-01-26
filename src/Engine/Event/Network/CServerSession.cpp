#include "CServerSession.h"
#include "CConnection.h"
#include "CServerClientSession.h"
#include <iostream>
#include <boost/asio.hpp>

#include "../../Misc/CTourException.h"
#include "../GameEvent/NetworkEvent.h"
#include "../CEventEngine.h"
#include "../../Log/CLog.h"

CServerSession::CServerSession(const UInt16& port, Int8 clientCount)
: m_io_service(), m_acceptor(m_io_service,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), m_id(1), m_clientCount(clientCount)
{
}

void CServerSession::listen()
{
	if(m_clientCount >= m_id)
	{
		//ecoute les connection
		CConnection_ptr connection(new CConnection(m_io_service));
		boost::shared_ptr<CServerClientSession> csession(new CServerClientSession(connection, m_id++,*this));
		m_acceptor.async_accept(connection->socket(),
			boost::bind(&CServerSession::handleAccept, this, csession,
			boost::asio::placeholders::error));
	}
}

void CServerSession::send(boost::shared_ptr<CEvent> event)
{
	if(event->getSource() == -1)
		event->setSource(0);
	m_io_service.post(boost::bind(&CServerSession::doSend, this, event));
}

void CServerSession::close()
{
	for(std::map<int,boost::shared_ptr<CServerClientSession> >::iterator i=m_clients.begin();
		i!=m_clients.end();i++)
	{
		m_io_service.post(boost::bind(&CServerClientSession::close, i->second));
	}
}

void CServerSession::close(int key)
{
	std::map<int,boost::shared_ptr<CServerClientSession> >::iterator clientit = m_clients.find(key);
	if(clientit!=m_clients.end())
		m_io_service.post(boost::bind(&CServerClientSession::close, clientit->second));
}

void CServerSession::run()
{
	try
	{
		m_io_service.run();
	}
	catch(CTourException e)
	{
		std::cerr << "Exception Tour : " << e.what();
	}
	catch(boost::system::system_error e)
	{
		std::cerr << e.what();
	}
	catch(std::runtime_error e)
	{
		std::cerr << e.what();
	}
	catch(...)
	{
		std::cerr << "Exception inconnue...";
	}

	CGameEngine::instance()->stop();
}

void CServerSession::handleAccept(boost::shared_ptr<CServerClientSession> session,
												const boost::system::error_code& error)
{
	if (!error)
	{
		m_clients[session->id()]=session;
		session->start();

		listen();
	}
	else
	{
		throw(std::runtime_error(error.message()));
	}
}


void CServerSession::doSend(boost::shared_ptr<CEvent> event)
{
	for(std::map<int,boost::shared_ptr<CServerClientSession> >::iterator i=m_clients.begin();
		i!=m_clients.end();i++)
	{
		i->second->send(event);			
	}
}

Int8 CServerSession::id()
{
	return 0;
}


void CServerSession::setClientState(UInt8 playerID, ClientState state)
{
	m_io_service.post(boost::bind(&CServerSession::doSetClientState, this, playerID, state));
}

void CServerSession::doSetClientState(UInt8 playerID, ClientState state)
{
	m_clients[playerID]->setState(state);

	if(m_clientCount == m_clients.size())
	{
		if(state == GAMELOADED && areAllClientState(GAMELOADED))
		{
			//Tout les joueur sont connecte
			CLog::debug("All player connected");
			boost::shared_ptr<CNetworkSyncPlayerDataEvent> syncPlayer(new CNetworkSyncPlayerDataEvent(m_clientCount));
			CGameEngine::instance()->getEventEngine()->pushEvent(syncPlayer);
		}
		else if(state == READY && areAllClientState(READY))
		{
			CLog::debug("All player ready");
			//La partie est pleine et peut commencer
			boost::shared_ptr<CNetworkStartGameEvent> event(new CNetworkStartGameEvent());
			CGameEngine::instance()->getEventEngine()->pushEvent(event);
		}
	}
}

bool CServerSession::areAllClientState(ClientState state)
{
	bool areAllReady = true;
	for(std::map<int,boost::shared_ptr<CServerClientSession> >::const_iterator i=m_clients.begin();
		i != m_clients.end(); i++)
		areAllReady &= (i->second->getState() == state);

	return areAllReady;
}


