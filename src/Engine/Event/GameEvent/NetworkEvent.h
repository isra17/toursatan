#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include "../CEvent.h"
#include "../Network/CServerClientSession.h"

//!Debute une session avec les clients
class CNetworkHelloEvent : public CEvent
{
public:
	//!unserialize l'objet
	CNetworkHelloEvent(std::istringstream& data);

	CNetworkHelloEvent(Int8 id);

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;

private:
	Int8 m_id;
};

//!Definis l'etat du client
class CNetworkClientStateEvent : public CEvent
{
public:
	//!unserialize l'objet
	CNetworkClientStateEvent(std::istringstream& data);

	CNetworkClientStateEvent(ClientState state);

	virtual void apply() const;
protected :
	ClientState m_state;

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;
};

//!Synchronise les donnees de joueur avec les clients
class CNetworkSyncPlayerDataEvent : public CEvent
{
public:
	//!unserialize l'objet
	CNetworkSyncPlayerDataEvent(std::istringstream& data);

	CNetworkSyncPlayerDataEvent(Int8 clientCount);

	virtual void apply() const;

	virtual bool onSend();
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;

private:
	std::vector<boost::shared_ptr<CHero> > m_heros;
	std::map<Int8, CBaseHandle> m_playersHero;
	Int8 m_clientCount;
};


//!Debute une partie avec les clients
class CNetworkStartGameEvent : public CEvent
{
public:
	//!unserialize l'objet
	CNetworkStartGameEvent(std::istringstream& data);

	CNetworkStartGameEvent();

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;

private:
};


#endif


