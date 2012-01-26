#include "NetworkEvent.h"
#include "../EventID.h"
#include "../Network/CClientEventEngine.h"
#include "../Network/CServerEventEngine.h"
#include "../../Entity/CHandle.h"
#include "../../Entity/GameEntity/CHero.h"
#include "../../Resource/CResourceEngine.h"
#include "../../Log/CLog.h"
#include "../../State/CStartGameState.h"
#include "../../Sound/CSoundEngine.h"

/******************************************************************************
/*								CNetworkHelloEvent
/******************************************************************************/

//unserialize l'objet
CNetworkHelloEvent::CNetworkHelloEvent(std::istringstream& data) : CEvent(EVENT_NETWORKHELLO)
{
	data >> m_id;
}

CNetworkHelloEvent::CNetworkHelloEvent(Int8 id) 
	: CEvent(EVENT_NETWORKHELLO), m_id(id)
{

}

void CNetworkHelloEvent::apply() const
{
	if(CGameEngine::instance()->isClient())
	{
		boost::shared_ptr<CClientEventEngine> eventEngine = 
			boost::shared_dynamic_cast<CClientEventEngine>(CGameEngine::instance()->getEventEngine());
		eventEngine->setConnectionID(m_id);

		CGameEngine::instance()->popState();
	}
}

//serialize l'objet
void CNetworkHelloEvent::serializeEvent(std::ostringstream& buffer) const
{
	buffer << m_id;
}


/******************************************************************************
/*						CNetworkClientStateEvent
/******************************************************************************/
//unserialize l'objet
CNetworkClientStateEvent::CNetworkClientStateEvent(std::istringstream& data)
: CEvent(EVENT_NETWORKCLIENTSTATE)
{
	UInt8 state;
	data.read((char*)&state, sizeof(UInt8));
	m_state = static_cast<ClientState>(state);
}

CNetworkClientStateEvent::CNetworkClientStateEvent(ClientState state)
: CEvent(EVENT_NETWORKCLIENTSTATE), m_state(state)
{
}

void CNetworkClientStateEvent::apply() const
{
	if(CGameEngine::instance()->isServer())
	{
		CLog::debug("Etat du client change");
		boost::shared_ptr<CServerEventEngine> serverEventEngine(
			boost::shared_dynamic_cast<CServerEventEngine>(CGameEngine::instance()->getEventEngine()));

		serverEventEngine->setClientState(getSource(), m_state);
	}
}

//serialize l'objet
void CNetworkClientStateEvent::serializeEvent(std::ostringstream& buffer) const
{
	UInt8 state = static_cast<UInt8>(m_state);
	buffer.write((char*)&state, sizeof(UInt8));
}

/******************************************************************************
/*						CNetworkSyncPlayerDataEvent
/******************************************************************************/

//unserialize l'objet
CNetworkSyncPlayerDataEvent::CNetworkSyncPlayerDataEvent(std::istringstream& data) : CEvent(EVENT_NETWORKSYNCPLAYERDATA)
{
	UInt8 size = m_playersHero.size();
	data.read((char*)&size, sizeof(UInt8));

	for(int i=0; i < size; i++)
	{
		UInt32 handle;
		sf::Vector2f coord;
		sf::Vector2f dim;

		data.read((char*)&handle, sizeof(UInt32));
		data.read((char*)&coord.x, sizeof(float));
		data.read((char*)&coord.y, sizeof(float));
		data.read((char*)&dim.x, sizeof(float));
		data.read((char*)&dim.y, sizeof(float));

		CBaseHandle hHandle(handle);
		boost::shared_ptr<CHero> newHero(new CHero(CGameEngine::instance()->getResEngine()->getModel("Hero")));
		newHero->setHandle(hHandle);
		newHero->setCoord(coord);
		newHero->setDim(dim);

		m_heros.push_back(newHero);
	}

	for(int i=0; i < size; i++)
	{
		Int8 id;
		UInt32 handle;

		data.read((char*)&id, sizeof(Int8));
		data.read((char*)&handle, sizeof(UInt32));

		m_playersHero[id] = handle;
	}
}

CNetworkSyncPlayerDataEvent::CNetworkSyncPlayerDataEvent(Int8 clientCount) 
	: CEvent(EVENT_NETWORKSYNCPLAYERDATA), m_clientCount(clientCount)
{
	
}

bool CNetworkSyncPlayerDataEvent::onSend()
{
	for(int i=1; i<=m_clientCount; i++)
		CGameEngine::instance()->addPlayer(i);

	std::map<Int8, CPlayer>& players = CGameEngine::instance()->m_players;
	for(std::map<Int8, CPlayer>::const_iterator i=players.begin(); i != players.end(); i++)
	{
		m_heros.push_back(i->second.getEntity());
		m_playersHero[i->first] = i->second.getEntity()->getHandle();
	}

	return true;
}

void CNetworkSyncPlayerDataEvent::apply() const
{
	if(CGameEngine::instance()->isClient())
	{
		foreach(boost::shared_ptr<CHero> hero, m_heros)
			CGameEngine::instance()->addEntity(hero, hero->getHandle());
	
		std::map<Int8, CPlayer>& players = CGameEngine::instance()->m_players;
		for(std::map<Int8, CBaseHandle>::const_iterator i=m_playersHero.begin(); i != m_playersHero.end(); i++)
		{
			CPlayer newPlayer;
			newPlayer.setEntity(CHandle(i->second).to<CHero>());
			players[i->first] = newPlayer;
		}

		//Le jeu est charge et pret a commencer
		boost::shared_ptr<CNetworkClientStateEvent> event(new CNetworkClientStateEvent(READY));
		CGameEngine::instance()->getEventEngine()->newEvent(event);
	}
}

//serialize l'objet
void CNetworkSyncPlayerDataEvent::serializeEvent(std::ostringstream& buffer) const
{
	UInt8 size = m_playersHero.size();
	buffer.write((char*)&size,sizeof(UInt8));

	foreach(boost::shared_ptr<CHero> hero, m_heros)
	{
		UInt32 handle = hero->getHandle();
		sf::Vector2f coord = hero->getCoord();
		sf::Vector2f dim = hero->getDim();

		buffer.write((char*)&handle,sizeof(UInt32));
		buffer.write((char*)&coord.x,sizeof(float));
		buffer.write((char*)&coord.y,sizeof(float));
		buffer.write((char*)&dim.x,sizeof(float));
		buffer.write((char*)&dim.y,sizeof(float));
	}

	for(std::map<Int8, CBaseHandle>::const_iterator i=m_playersHero.begin(); i != m_playersHero.end(); i++)
	{
		Int8 id = i->first;
		UInt32 handle = i->second;

		buffer.write((char*)&id,sizeof(Int8));
		buffer.write((char*)&handle,sizeof(UInt32));
	}
}


/******************************************************************************
/*								CNetworkStartGameEvent
/******************************************************************************/

//unserialize l'objet
CNetworkStartGameEvent::CNetworkStartGameEvent(std::istringstream& data) : CEvent(EVENT_NETWORKSTARTGAME)
{

}

CNetworkStartGameEvent::CNetworkStartGameEvent() : CEvent(EVENT_NETWORKSTARTGAME)
{

}

void CNetworkStartGameEvent::apply() const
{
	CLog::debug("Debut de la partie");
	boost::shared_ptr<CStartGameState>  startGameState(new CStartGameState(5));
	CGameEngine::instance()->popState();
	CGameEngine::instance()->pushState(startGameState);
	CGameEngine::instance()->start();

	//Start la music
	boost::shared_ptr<CSoundEngine> soundEngine(CGameEngine::instance()->getSoundEngine());
	if(soundEngine)
		soundEngine->getMusic().Play();
}

//serialize l'objet
void CNetworkStartGameEvent::serializeEvent(std::ostringstream& buffer) const
{

}