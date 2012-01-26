#include "CClientSession.h"

#include <iostream>

#include "../CEventEngine.h"
#include "../CEventFactory.h"
#include "../../CGameEngine.h"
#include "../../Misc/CTourException.h"
#include "../../Log/CLog.h"


CClientSession::CClientSession()
: m_io_service(), m_connection(new CConnection(m_io_service)),m_resolver(m_io_service), m_id(-1)
{
}

void CClientSession::connect(const std::string& host, const std::string& port)
{
	//Requete pour trouver l'adresse du serveur	
	boost::asio::ip::tcp::resolver::query query(host, port);
	boost::asio::ip::tcp::resolver::iterator iter = m_resolver.resolve(query);

	m_io_service.post(boost::bind(&CClientSession::doConnect, this, iter));
}


void CClientSession::send(boost::shared_ptr<CEvent> event)
{
	m_io_service.post(boost::bind(&CClientSession::doSend, this, event));
}

void CClientSession::close()
{
	m_io_service.post(boost::bind(&CClientSession::doClose, this));
}

void CClientSession::run()
{
	try
	{
		m_io_service.run();
	}
	catch(CTourException e)
	{
		CLog::error(std::string("Exception Tour : ") + e.what());
	}
	catch(boost::system::system_error e)
	{
		CLog::error(e.what());
	}
	catch(std::runtime_error e)
	{
		CLog::error(e.what());
	}
	catch(...)
	{
		CLog::error("Exception inconnue...");
	}
	
	CGameEngine::instance()->stop();
}

void CClientSession::doConnect(boost::asio::ip::tcp::resolver::iterator endpoint)
{
	m_connection->socket().async_connect(*endpoint,
		boost::bind(&CClientSession::handleConnect, this,
					boost::asio::placeholders::error, ++endpoint));
}

void CClientSession::handleConnect(const boost::system::error_code& error,
									boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (!error)
	{
		CLog::debug("Client connecté au serveur");

		m_connection->socket().set_option(boost::asio::ip::tcp::no_delay(true));

		//Connection reussi
		m_connection->asyncRead(m_readBuffer,
		boost::bind(&CClientSession::handleRead, this,
			boost::asio::placeholders::error));
	}
	else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
	{
		//retentative de connection
		m_connection->socket().async_connect(*endpoint_iterator,
			boost::bind(&CClientSession::handleConnect, this,
			boost::asio::placeholders::error, ++endpoint_iterator));
	}
	else
	{
		//Connection impossible
		throw(std::runtime_error(error.message()));
	}
}

void CClientSession::doSend(boost::shared_ptr<CEvent> event)
{
	const std::string& binEvent(event->serialize());

	//Ajoute le paquet a la pile d'envoi
	bool write_in_progress = !m_sendBuffers.empty();
	m_sendBuffers.push(binEvent);
	if (!write_in_progress)
	{
		m_connection->asyncWrite(m_sendBuffers.front(),
			boost::bind(&CClientSession::handleSend, this,
				boost::asio::placeholders::error));
	}
}

void CClientSession::handleSend(const boost::system::error_code& error)
{
	if (!error)
	{
		m_sendBuffers.pop();
		if (!m_sendBuffers.empty())
		{
			m_connection->asyncWrite(m_sendBuffers.front(),
				boost::bind(&CClientSession::handleSend, this,
					boost::asio::placeholders::error));
		}
	}
	else
	{
		//Impossible d'envoyer au serveur
		throw(std::runtime_error(error.message()));
		doClose();
	}
}

void CClientSession::doClose()
{
	//Fermeture de la connection (detruit le pointeur de m_connection)
	m_connection.reset();
}

void CClientSession::handleRead(const boost::system::error_code& error)
{
	if (!error)
	{
		UInt16 eventID = *((UInt16*)m_readBuffer.c_str());
		boost::shared_ptr<CEvent> event = CEventFactory::build(eventID,m_readBuffer);
		CGameEngine::instance()->getEventEngine()->pushEvent(event);

		m_connection->asyncRead(m_readBuffer,
			boost::bind(&CClientSession::handleRead, this,
				boost::asio::placeholders::error));
	}
	else
	{
		//Message d'erreur recu (deconnection?)
		throw(std::runtime_error(error.message()));
		doClose();
	}
}


Int8 CClientSession::id()
{
	return m_id;
}

void CClientSession::setId(Int8 id)
{
	m_id = id;
}

bool CClientSession::isConnected()
{
	return m_connection->socket().is_open();
}