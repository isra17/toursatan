#ifndef CSERVERCLIENTSESSION_H
#define CSERVERCLIENTSESSION_H

#include "../CEvent.h"
#include "CConnection.h"
#include <queue>

class CServerSession;


enum ClientState{
	NOTREADY=0,
	GAMELOADED=1,
	READY=2
};

//!Session d'un client sur le serveur
class CServerClientSession
{
    public:
		CServerClientSession(CConnection_ptr connection, Int8 id, CServerSession& server);
		
		//Retourne le socket de la session
		boost::asio::ip::tcp::socket& socket();
		
		//Initialise la session
		void start();		
		//Ferme la session
		void close();
		//Envoi un events au client
		void send(boost::shared_ptr<CEvent> event);
		//ID du client
		Int8 id();
		//Definit l'etat du client
		void setState(ClientState state);
		//Retourne l'etat du client
		ClientState getState();
	private:
		//Callback lorsque des donnees ont ete envoyée
		void handleSend(const boost::system::error_code& error);

		//Callback lorsque des données ont été reçu
		void handleRead(const boost::system::error_code& error);

		//Instance de la connexion
		CConnection_ptr m_connection;

		//ID du client
		Int8 m_id;
		//état du client
		ClientState m_state;

		//Buffer des paquet à envoyer
		std::queue<const std::string > m_sendBuffers;
		//Buffer de lecture
		std::string m_readBuffer;

		//Session serveur
		CServerSession& m_server;
};

#endif // CHU_CCLIENTSESSION_H
