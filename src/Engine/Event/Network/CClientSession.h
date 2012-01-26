#ifndef CCLIENTSESSION_H
#define CCLIENTSESSION_H

#include <boost/asio.hpp>
#include <queue>
#include "../CEvent.h"
#include "INetworkSession.h"
#include "CConnection.h"

//!Session d'un client
class CClientSession : public INetworkSession
{
    public:
		CClientSession();
		/*!
		*	Connecte le client a un serveur distant
		*	\param	host	Adresse du serveur distant
		*	\param	port	Port du serveur distant
		*/
		virtual void connect(const std::string& host, const std::string& port);
		
		//!Envoie un event au serveur
		virtual void send(boost::shared_ptr<CEvent> event);
		//!Ferme la connexion
		virtual void close();

		//!Lance le service (bloquant)
		virtual void run();

		//!Retourne l'ID du client
		Int8 id();
		//!Definit l'ID du client
		void setId(Int8 id);

		//!Retourne si la session est connectée
		bool isConnected();
	private:
		//Connecte au serveur
		void doConnect(boost::asio::ip::tcp::resolver::iterator endpoint);

		//Callback lorsque le client est connectee
		void handleConnect(const boost::system::error_code& error,
							boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

		//Envoie des donnes
		void doSend(boost::shared_ptr<CEvent> event);
		//Callback apres l'envoi de donnee
		void handleSend(const boost::system::error_code& error);

		//Ferme la connexion
		void doClose();
		//Callback lorsque des donnes sont recu
		void handleRead(const boost::system::error_code& error);

		//service Asio
		boost::asio::io_service m_io_service;
		//Trouve un adresse IP valide
		boost::asio::ip::tcp::resolver m_resolver;		
		//Instance de la connexion
		CConnection_ptr m_connection;

		//Buffer des paquet a envoyer
		std::queue<const std::string > m_sendBuffers;
		//Buffer du paquet recu
		std::string m_readBuffer;

		//ID du client
		Int8 m_id;

};

#endif // CHU_CCLIENTSESSION_H
