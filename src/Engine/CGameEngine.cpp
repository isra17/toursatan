#include "CGameEngine.h"

#include "Log/CLog.h"

#include "Entity/IEntity.h"
#include "Entity/CEntityList.h"

#include "Entity/GameEntity/CHero.h"
#include "Entity/GameEntity/CDemon.h"
#include "Entity/GameEntity/CDebris.h"
#include "Entity/GameEntity/CSatan.h"
#include "Entity/GameEntity/CPofin.h"

#include "Level/CLevel.h"
#include "Level/CLevelLoader.h"

#include "Event/CEventEngine.h"
#include "Event/GameEvent/HeroEvent.h"
#include "Event/GameEvent/NetworkEvent.h"
#include "Resource/CResourceEngine.h"

#include "Graphics/Model/CRectModel.h"
#include "Graphics/Model/CSatanModel.h"

#include "State/CPlayGameState.h"
#include "State/CWaitState.h"
#include "State/CGameWonState.h"
#include "State/CGameLostState.h"

#include "Misc/CTourException.h"

#include "Sound/CSoundEngine.h"

#include <SFML/System.hpp>
#include <boost/property_tree/info_parser.hpp>


boost::shared_ptr<CGameEngine> CGameEngine::m_instance;

//!Initialise le game engine
CGameEngine::CGameEngine(bool isServer) 
: m_level(new CLevel()), m_resourceEngine(new CResourceEngine()), m_isServer(isServer)
{
	
}

void CGameEngine::initGame()
{
	try{
		boost::property_tree::ptree levelRoot;
		read_info("data\\test_level.info", levelRoot);

		CLevelLoader::load(levelRoot, m_level,m_resourceEngine);
	}
	catch(boost::property_tree::ptree_error &e){
		CLog::error(e.what());
	}
	m_level->setSpeed(100.0f);

	boost::shared_ptr<CPlayGameState> gameState(new CPlayGameState());
	pushState(gameState);

	boost::shared_ptr<CWaitState> waitState(new CWaitState());
	pushState(waitState);

	m_isRunning=true;
}

CGameEngine::~CGameEngine()
{
	
}

int CGameEngine::run()
{
	initGame();
	initEngine();

	float lastTime = 0.f;
	m_clock.stop();

	while (m_isRunning)
    {
		float currentTime = m_clock.getTick();
		float elapsedtime = currentTime-lastTime;

		lastTime = currentTime;

		do
		{
			float reducedTime = std::min(0.033f, elapsedtime);
			assert(reducedTime >= 0 && reducedTime <= 0.033f);
			elapsedtime -= 0.033f;

			update(reducedTime);
		
			m_eventEngine->onFrame(reducedTime);

			if(!m_stateStack.empty())
				m_stateStack.top()->update(reducedTime);
		}while(elapsedtime > 0);
    }

	return 0;
}

void CGameEngine::updateEntity(float elapsedTime)
{
	if(elapsedTime > 0)
	{
		m_isIteraring=true;
		//Met a jour le level
		m_level->update(elapsedTime);

		//Met a jour les entity
		CLevel::TEntitySet entityList = m_level->getScreenEntities();
		for(CLevel::TItEntity itEnt = entityList.begin();itEnt!=entityList.end();itEnt++)
		{
			(*itEnt)->update(elapsedTime);
		}
		m_isIteraring=false;

		//Supprime les entity a supprimer
		cleanEntityToDelete();
	}
}

void CGameEngine::start()
{
	m_clock.play();
}

void CGameEngine::stop()
{
	m_isRunning = false;
}

void CGameEngine::pause()
{
	m_clock.pause();
}

void CGameEngine::pushState(boost::shared_ptr<IState> newState)
{
	assert(newState != boost::shared_ptr<IState>());
	newState->begin();
	m_stateStack.push(newState);
}

boost::shared_ptr<IState> CGameEngine::topState()
{
	return m_stateStack.top();
}


boost::shared_ptr<IState> CGameEngine::popState()
{
	boost::shared_ptr<IState> state = m_stateStack.top();
	state->end();
	m_stateStack.pop();
	return state;
}

boost::shared_ptr<CEventEngine> CGameEngine::getEventEngine()
{
	return m_eventEngine;
}

boost::shared_ptr<CResourceEngine> CGameEngine::getResEngine()
{
	return m_resourceEngine;
}

boost::shared_ptr<CRenderEngine> CGameEngine::getRenderEngine()
{
	return m_renderEngine;
}

boost::shared_ptr<CSoundEngine> CGameEngine::getSoundEngine()
{
	return m_soundEngine;
}

//Ajoute une entity au jeu
CBaseHandle CGameEngine::addEntity(boost::shared_ptr<IEntity> entity)
{
	assert(!entity->getHandle().isValid());
	CBaseHandle handle = m_level->addEntity(entity);
	return handle;
}

void CGameEngine::addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle)
{
	assert(handle.isValid());
	m_level->addEntity(entity,handle);
}

//!Supprime un entity du jeu. fromEntity doit etre a true si une entity veut se supprimer elle-meme du jeu.
void CGameEngine::deleteEntity(const CBaseHandle& handle, bool fromEntity)
{	
	if(m_isIteraring && fromEntity)
		m_entityToDelete.push(handle);
	else
		m_level->removeEntity(handle);		
}

//!Retourne un entity a partir de son handle
boost::shared_ptr<IEntity> CGameEngine::findEntity(const CBaseHandle& handle) const
{
	return m_level->getEntityList()->getEntity(handle);
}

boost::shared_ptr<CEntityList> CGameEngine::getEntityList() const
{
	return m_level->getEntityList();
}


//!Retourne la liste d'entity presentement dans l'ecran
CLevel::TEntitySet CGameEngine::getScreenEntities() const
{
	return m_level->getScreenEntities();
}

void CGameEngine::cleanEntityToDelete()
{
	while(!m_entityToDelete.empty())
	{
		deleteEntity(m_entityToDelete.top());
		m_entityToDelete.pop();
	}
}

void CGameEngine::setEventEngine(boost::shared_ptr<CEventEngine> eventEngine)
{
	m_eventEngine = eventEngine;
}

void CGameEngine::setRenderEngine(boost::shared_ptr<CRenderEngine> renderEngine)
{
	m_renderEngine = renderEngine;
}

void CGameEngine::setSoundEngine(boost::shared_ptr<CSoundEngine> soundEngine)
{
	m_soundEngine = soundEngine;
}

CPlayer& CGameEngine::getPlayer(Int8 id) 
{
	return m_players[id];
}

const std::map<Int8, CPlayer>& CGameEngine::getPlayerList() const
{
	return m_players;
}

Int8 CGameEngine::getLocalPlayerId() const
{
	return 0;
}

sf::FloatRect CGameEngine::getScreenRect() const
{
	return m_level->getScreenRect();
}

boost::shared_ptr<CLevel> CGameEngine::getLevel() const
{
	return m_level;
}

void CGameEngine::addPlayer(Int8 id)
{
	CLog::debug("New player added");

	std::vector<sf::Vector2f> spawns = m_level->getSpawnLocation();
	if(static_cast<Int8>(spawns.size()) >= id)
	{
		sf::Vector2f coord = spawns[id-1];
		boost::shared_ptr<CHero> newHero(new CHero(m_resourceEngine->getModel("Hero")));
		newHero->setCoord(coord);
		newHero->setDim(sf::Vector2f(45.f,90.f));
		
		addEntity(newHero);

		CPlayer newPlayer;
		newPlayer.setEntity(newHero);
		m_players.insert(std::make_pair(id,newPlayer));
	}
	else
		throw(CTourException("id > spawns.size()"));
}

//Retourne si c'est un serveur ou un client
bool CGameEngine::isServer() const
{
	return m_isServer;
}

bool CGameEngine::isClient() const
{
	return !m_isServer;
}

void CGameEngine::winGame()
{
	CLog::debug("Partie gagne");
	pause();
	boost::shared_ptr<CGameWonState> winState(new CGameWonState());
	pushState(winState);
}

//Notifie le jeu qu'un Hero est mort
void CGameEngine::heroDied(boost::shared_ptr<CHero> deadHero)
{
	deadHero->setActive(false);

	bool areAllPlayerDead = true;
	for(std::map<Int8, CPlayer>::const_iterator i=m_players.begin(); i != m_players.end(); i++)
		if(i->second.getEntity()->isActive())
			areAllPlayerDead = false;

	if(areAllPlayerDead)
	{
		CLog::debug("Partie perdu");
		pause();
		boost::shared_ptr<CGameLostState> loseState(new CGameLostState());
		pushState(loseState);
	}
	else
	{
		boost::shared_ptr<IModel> satanModel = getResEngine()->getModel("Satan");
		satanModel->setAnim("Fly");
		boost::shared_ptr<CSatanModel> model(new CSatanModel(deadHero->getModel(),satanModel));
		boost::shared_ptr<IEntity> satan(new CSatan(200,deadHero,model));
		satan->setDim(sf::Vector2f(140,200));
		addEntity(satan);
	}
}


void CGameEngine::addScore(boost::shared_ptr<IEntity> playerHero, UInt32 score)
{
	if(isServer())
	{
		UInt8 playerId=-1;
		for(std::map<Int8, CPlayer>::const_iterator i=m_players.begin();i!=m_players.end();i++)
			if(playerHero == i->second.getEntity())
				playerId = i->first;

		if(playerId != 0)
		{
			boost::shared_ptr<CHeroAddScore> addScoreEvent(new CHeroAddScore(playerId,score));
			m_eventEngine->newEvent(addScoreEvent);
		}
	}
}

