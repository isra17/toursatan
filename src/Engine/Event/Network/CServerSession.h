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
		*	\param	port	Port d'écoute
		*	\param	clientCount	Nombre de clients
		**/
		CServerSession(const unsigned short& port, Int8 clientCount);
		//!Écoute les connexions
		virtual void listen();
		//!Envoie un event à tout les clients
		virtual void send(boost::shared_ptr<CEvent> event);
		//!Ferme les sessions avec les clients
		virtual void close();
		//!Ferme une session d'un client
		void close(int key);

		//!Exécute le service (bloquant)
		virtual void run();

		//!Envoi un event à un client
		void sendTo();

		//!Retourne l'ID du serveur
		Int8 id();

		//!Définit l'état d'un client
		void setClientState(UInt8 playerID, ClientState state);
		
	private:
		//Définit l'état d'un client
		void doSetClientState(UInt8 playerID, ClientState state);
		//Véréfie si tout les client sont d'un états
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
