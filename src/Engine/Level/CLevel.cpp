#include "CLevel.h"
#include "../Util.h"

CLevel::CLevel()
: m_entityList(new CEntityList()), m_screenRect(0,-769,800,0), m_speed(0.f), m_endLevel(0.f)
{

}

//Met a jour le level (enleve les entity plus a l'ecran et rajoute les nouvelles)
void CLevel::update(float elapsedTime)
{
	float offset = -m_speed*elapsedTime;

	//Arrete le defilement a la fin de l'ecran
	if(m_screenRect.Top + offset +400 <= m_endLevel)
		offset = m_endLevel - (m_screenRect.Top + 400);

	//Deplace l'ecran
	m_screenRect.Offset(0,offset);
	
	//Suprimme les entity qui sont hors de l'ecran
	foreach(boost::shared_ptr<IEntity> ent, m_screenEntity)
	{
		if(ent->getCoord().y > m_screenRect.Bottom + 100)
			ent->outOfRange();
	}

	//Ajoute les entity qui entre dans l'ecran
	std::vector<boost::weak_ptr<IEntity> > elemToDelete;
	foreach(boost::weak_ptr<IEntity> wEnt, m_screenQueue)
	{
		boost::shared_ptr<IEntity> ent = wEnt.lock();
		if(ent)
		{
			if(ent->getCoord().y + ent->getDim().y > m_screenRect.Top - 100)
			{
				elemToDelete.push_back(ent);
				m_screenEntity.insert(ent);
			}
		}
	}
	foreach(boost::weak_ptr<IEntity> ent, elemToDelete)
		m_screenQueue.erase(ent);

	//Definit la partie du fond affiche
	unsigned int backgroundHeight = m_backgroundSprite->GetImage()->GetHeight() - static_cast<int>(m_screenRect.GetHeight());

	float repBackground = (m_endLevel - m_screenRect.Bottom) / m_endLevel;
	assert(repBackground >= 0 && repBackground <= 1);

	unsigned int topBackground = static_cast<int>(backgroundHeight*repBackground);
	sf::IntRect backgroundRect(0,
								topBackground,
								static_cast<int>(m_screenRect.GetWidth()),
								topBackground + static_cast<int>(m_screenRect.GetHeight()));
	m_backgroundSprite->SetSubRect(backgroundRect);
}

//!Ajoute un entity
CBaseHandle CLevel::addEntity(boost::shared_ptr<IEntity> entity)
{
	if(entity)
	{
		m_screenQueue.insert(entity);
		return m_entityList->addEntity(entity);
	}
	return CBaseHandle();
}

void CLevel::addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle)
{
	boost::shared_ptr<IEntity> oldEntity = m_entityList->getEntity(handle);
	if(oldEntity)
		removeEntity(handle);

	if(entity)
	{
		m_screenQueue.insert(entity);
		m_entityList->addEntity(entity,handle);
	}
}

//!Enleve un entity
void CLevel::removeEntity(CBaseHandle handle)
{
	boost::shared_ptr<IEntity> ent = m_entityList->removeEntity(handle);

	m_screenQueue.erase(ent);
	m_screenEntity.erase(ent);
}

//!Retourne la liste d'entity du jeu
boost::shared_ptr<CEntityList> CLevel::getEntityList() const
{
	return m_entityList;
}

//!Retourne la liste d'entity presentement dans l'ecran
CLevel::TEntitySet CLevel::getScreenEntities() const
{
	return m_screenEntity;
}

//Tri les entity
bool CLevel::m_OrderEntity::operator()(boost::weak_ptr<IEntity> wEnt1,boost::weak_ptr<IEntity> wEnt2)
{
	boost::shared_ptr<IEntity> ent1 = wEnt1.lock();
	boost::shared_ptr<IEntity> ent2 = wEnt2.lock();
	if(ent1)
	{
		if(ent2)
		{
			float y1 = ent1->getCoord().y+ent1->getDim().y;
			float y2 = ent2->getCoord().y+ent2->getDim().y;
			if(y1 == y2)
				return ent1 < ent2;

			return y1 > y2;
		}
		else
			return false;
	}
	else
		return true;
}


void CLevel::setSpeed(float speed)
{
	m_speed = speed;
}

sf::FloatRect CLevel::getScreenRect() const
{
	return m_screenRect;
}

void CLevel::setEndLevel(float endLevel)
{
	m_endLevel = endLevel;
}

float CLevel::getEndLevel()
{
	return m_endLevel;
}


//Definit les points de spawn pour les joueurs
std::vector<sf::Vector2f> CLevel::getSpawnLocation() const
{
	return m_spawnLocation;
}

void CLevel::addSpawnLocation(sf::Vector2f spawnLocation)
{
	m_spawnLocation.push_back(spawnLocation);
}

bool CLevel::isEndReached()
{
	return m_screenRect.Top + 400 <= m_endLevel;
}


void CLevel::setBackgroundSprite(boost::shared_ptr<sf::Sprite> backgroundSprite)
{
	m_backgroundSprite = backgroundSprite;
	
}


boost::shared_ptr<sf::Sprite> CLevel::getBackgroundSprite()
{
	return m_backgroundSprite;
}

void CLevel::setBorderSprite(boost::shared_ptr<sf::Sprite> borderSprite)
{
	m_borderSprite = borderSprite;
	
}

boost::shared_ptr<sf::Sprite> CLevel::getBorderSprite()
{
	return m_borderSprite;
}
void CLevel::setScreenSize(sf::Vector2i size)
{
	assert(m_screenRect.Bottom == 0);
	m_screenRect.Top = -size.y;
	m_screenRect.Right = size.x;
}




