#ifndef CCLIENTEVENTENGINE_H
#define CCLIENTEVENTENGINE_H

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "../CEventEngine.h"
#include "../../Misc/BasicType.h"

class CClientSession;

//!Moteur d'evenement pour le client
class CClientEventEngine : public CEventEngine
{
public:
	CClientEventEngine(boost::shared_ptr<CClientSession> session);

	//!Cree un nouvel event
	virtual void newEvent(CEventEngine::EventPtr event);

	//!Retourne l'ID du client
	Int8 getConnectionID() const;
	//!Definit l'ID du client
	void setConnectionID(Int8 id);

private:
	boost::shared_ptr<CClientSession> m_session;
	boost::thread m_sessionThread;
};

#endif //CCLIENTEVENTENGINE_H