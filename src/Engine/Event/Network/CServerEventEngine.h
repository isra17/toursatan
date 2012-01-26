#ifndef CSERVEREVENTENGINE_H
#define CSERVEREVENTENGINE_H

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "../CEventEngine.h"

class CServerSession;

//!Moteur d'événement serveur
class CServerEventEngine : public CEventEngine
{
public:
	CServerEventEngine(boost::shared_ptr<CServerSession> session);

	//!Cree un nouvelle event (a utiliser pour lancer un evenement en temps normal)
	virtual void newEvent(CEventEngine::EventPtr event);

	//!Procede un evenement de jeux 
	virtual void handleEvent(CEventEngine::EventPtr event);

	//!Retourne l'ID du serveur
	Int8 getConnectionID() const;
	//!Définit l'ID du serveur
	void setClientState(UInt8 playerID, UInt8 stateID);
private:
	boost::shared_ptr<CServerSession> m_session;
	boost::thread m_sessionThread;
};

#endif //CSERVEREVENTENGINE_H