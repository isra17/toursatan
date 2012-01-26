#ifndef CLEVEL_H
#define CLEVEL_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>

#include "../Entity/CBaseHandle.h"

class IEntity;
class CEntityList;

//!Définit un niveau de jeu
class CLevel
{
public:
	typedef std::set<boost::shared_ptr<IEntity> > TEntitySet;
	typedef TEntitySet::iterator TItEntity;

	CLevel();

	//!Met a jour le level (enleve les entity plus a l'ecran et rajoute les nouvelles)
	void update(float elapsedTime);

	//!Ajoute un entity
	CBaseHandle addEntity(boost::shared_ptr<IEntity> entity);
	//!Ajoute une entity au jeu avec un handle precis (remplace l'entity existante si il y en a une deja)
	void addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle);
	//!Enleve un entity
	void removeEntity(CBaseHandle hHandle);

	//!Retourne la liste d'entity du jeu
	boost::shared_ptr<CEntityList> getEntityList() const;
	//!Retourne la liste d'entity presentement dans l'ecran
	TEntitySet getScreenEntities() const;

	//! defini la vitesse de l'ecran
	void setSpeed(float speed);
	sf::FloatRect getScreenRect() const;

	//!Definit la fin du level
	void setEndLevel(float endLevel);
	float getEndLevel();

	//!Retourne true si la fin du defilement est atteinte
	bool isEndReached();

	//!Definit les points de spawn pour les joueurs
	std::vector<sf::Vector2f> getSpawnLocation() const;
	void addSpawnLocation(sf::Vector2f spawnLocation);

	//!Definit le fond de jeu
	void setBackgroundSprite(boost::shared_ptr<sf::Sprite>);
	boost::shared_ptr<sf::Sprite> getBackgroundSprite();
	void setBorderSprite(boost::shared_ptr<sf::Sprite>);
	boost::shared_ptr<sf::Sprite> getBorderSprite();

	//!Definit la taille de l'ecran de jeu (ne devrait pas etre appeler apres le demarrage de jeu)
	void setScreenSize(sf::Vector2i size);
private:
	class m_OrderEntity
	{
	public:
		bool operator()(boost::weak_ptr<IEntity> wEnt1,boost::weak_ptr<IEntity> wEnt2);
	};

	typedef std::set<boost::weak_ptr<IEntity>, m_OrderEntity> TEntityQueue;
	typedef TEntityQueue::iterator TItEntityQueue;

	float m_speed;

	boost::shared_ptr<CEntityList> m_entityList;
	TEntitySet m_screenEntity;
	TEntityQueue m_screenQueue;

	std::vector<sf::Vector2f> m_spawnLocation;

	sf::FloatRect m_screenRect;
	float m_endLevel;

	boost::shared_ptr<sf::Sprite> m_backgroundSprite;
	boost::shared_ptr<sf::Sprite> m_borderSprite;
};

#endif

