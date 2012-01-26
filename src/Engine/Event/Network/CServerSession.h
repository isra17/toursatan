#ifndef CSERVERSESSION_H
#define CSERVERSESSION_H

#include "../CEvent.h"
#include "INetworkSession.h"
#include <map>
#include <boost/asio.hpp>
#include "CServerClientSession.h"

//!Session du serveur
class CServerSession : public INetworkSession
{
    public:
		/*!
		*	\param	port	Port d'�coute
		*	\param	clientCount	Nombre de clients
		**/
		CServerSession(const unsigned short& port, Int8 clientCount);
		//!�coute les connexions
		virtual void listen();
		//!Envoie un event � tout les clients
		virtual void send(boost::shared_ptr<CEvent> event);
		//!Ferme les sessions avec les clients
		virtual void close();
		//!Ferme une session d'un client
		void close(int key);

		//!Ex�cute le service (bloquant)
		virtual void run();

		//!Envoi un event � un client
		void sendTo();

		//!Retourne l'ID du serveur
		Int8 id();

		//!D�finit l'�tat d'un client
		void setClientState(UInt8 playerID, ClientState state);
		
	private:
		//D�finit l'�tat d'un client
		void doSetClientState(UInt8 playerID, ClientState state);
		//V�r�fie si tout les client sont d'un �tats
		bool areAllClientState(ClientState state);
		//Callback lors de la connexion d'un client
		void handleAccept(boost::shared_ptr<CServerClientSession> session,
					const boost::system::error_code& error);
		
		//Envoi d'un event
		void doSend(boost::shared_ptr<CEvent> event);

		boost::asio::io_service m_io_service;	
		boost::asio::ip::tcp::acceptor m_acceptor;

		//Liste des session clients
		std::map<int,boost::shared_ptr<CServerClientSession> > m_clients;

		Int8 m_id;
		Int8 m_clientCount;
};

#endif // CHU_CSERVERSESSION_H
