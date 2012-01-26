#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H

#include <boost/shared_ptr.hpp>
#include <stack>
#include <vector>
#include <set>

#include "Misc/CClock.h"
#include "Misc/BasicType.h"
#include "Entity/CBaseHandle.h"


#include "CPlayer.h"

#include <SFML/Graphics.hpp>

class CEventEngine;
class CResourceEngine;
class CRenderEngine;
class CSoundEngine;

class IEntity;
class Chero;
class CEntityList;
class CLevel;
class IState;

//!Le moteur de jeu
class CGameEngine
{
public:
	virtual ~CGameEngine();

	//!Initialise le jeu
	void initGame();

	//!Initialise le jeu selon si c'est le server ou client
	virtual void initEngine()=0;

	int run();

	//!Update les entity
	void updateEntity(float elapsedTime);

	//!Met l'horloge de jeu en marche
	void start();
	//!Met l'horloge de jeu en pause
	void pause();
	//!Arrete le jeu
	void stop();

	//!Ajoute un état
	void pushState(boost::shared_ptr<IState> newState);
	//!Retourne l'état courant
	boost::shared_ptr<IState> topState();
	//!Retire l'état courant
	boost::shared_ptr<IState> popState();

	boost::shared_ptr<CEventEngine> getEventEngine();
	boost::shared_ptr<CResourceEngine> getResEngine();
	boost::shared_ptr<CRenderEngine> getRenderEngine();
	boost::shared_ptr<CSoundEngine> getSoundEngine();
	
	//!Retourne un entity a partir de son handle
	boost::shared_ptr<IEntity> findEntity(const CBaseHandle& handle) const;
	//!Ajoute une entity au jeu
	CBaseHandle addEntity(boost::shared_ptr<IEntity> entity);
	//!Ajoute une entity au jeu avec un handle precis (remplace l'entity existante si il y en a une deja)
	void addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle);
	//!Supprime un entity du jeu. fromEntity doit etre a true si une entity veut se supprimer elle-meme du jeu.
	void deleteEntity(const CBaseHandle& handle, bool fromEntity=false);
	
	//!Retourne la liste d'entity du jeu
	boost::shared_ptr<CEntityList> getEntityList() const;
	//!Retourne la liste d'entity presentement dans l'ecran
	std::set<boost::shared_ptr<IEntity> > getScreenEntities() const;

	//!Retourne le level
	boost::shared_ptr<CLevel> getLevel() const;
	//!Retourne le rectangle de l'écran de jeu
	sf::FloatRect getScreenRect() const;

	//!Retourne une stucture de joueur
	CPlayer& getPlayer(Int8 id);
	//!Retourne la liste de joueur
	const std::map<Int8, CPlayer>& getPlayerList() const;
	//!Retourne l'ID du joueur local
	virtual Int8 getLocalPlayerId() const;

	//!Retourne si c'est un serveur
	bool isServer() const;
	//!Retourne si c'est un client
	bool isClient() const;

	//!Ajoute un nouveau joueur au jeu
	void addPlayer(Int8 id);

	//!Notifie le jeu que les joueurs ont gagnées
	void winGame();
	//!Notifie le jeu qu'un Hero est mort
	void heroDied(boost::shared_ptr<CHero> deadHero);

	//!Ajoute un montant de score à un client
	void addScore(boost::shared_ptr<IEntity> playerHero, UInt32 score);
protected:
	//!definit le moteur d'event
	void setEventEngine(boost::shared_ptr<CEventEngine> eventEngine);
	//!definit le moteur graphiqe
	void setRenderEngine(boost::shared_ptr<CRenderEngine> renderEngine);
	//!definit le moteur de son
	void setSoundEngine(boost::shared_ptr<CSoundEngine> soundEngine);

	//!update le jeu
	virtual void update(float elapsedTime)=0;
private:

	//!Supprime la liste d'entity a supprimer
	void cleanEntityToDelete();

	//!Si on est en train d'iterer les entity (il ne faut pas invalider l'iterateur)
	bool m_isIteraring;
	//!Pile d'entity a supprimer apres lorsque on peut
	std::stack<CBaseHandle> m_entityToDelete;

	//!Information des joueurs
	std::map<Int8, CPlayer> m_players;

	boost::shared_ptr<CResourceEngine> m_resourceEngine;
	boost::shared_ptr<CEventEngine> m_eventEngine;
	boost::shared_ptr<CRenderEngine> m_renderEngine;
	boost::shared_ptr<CSoundEngine> m_soundEngine;

	//Level et les entités du jeu
	boost::shared_ptr<CLevel> m_level;

	//Pile d'état
	std::stack<boost::shared_ptr<IState> > m_stateStack;

	bool m_isRunning;
	CClock m_clock;

	bool m_isServer;

	friend class CNetworkSyncPlayerDataEvent;

//////////////////////////////////////////////////
////////////Implementation du Singleton///////////
//////////////////////////////////////////////////
public:	
	static boost::shared_ptr<CGameEngine> instance()
	{
		return m_instance;
	}

protected:
	static void init(boost::shared_ptr<CGameEngine> newInstance)
	{
		m_instance = newInstance;
	}

	CGameEngine(bool isServer);

private:
	static boost::shared_ptr<CGameEngine> m_instance;

	CGameEngine(const CGameEngine&);
};

#endif // CGAMEENGINE_H