#include "CDebris.h"
#include "CHero.h"

#include "../../Util.h"

CDebris::CDebris(boost::shared_ptr<IModel> model) 
: IEntity(model), SPEED(200.f)
{
}

void CDebris::update(float timeElapsed)
{
	m_speed.y = SPEED;
	sf::Vector2f coord = getCoord();
	sf::Vector2f move = m_speed;
	move *= timeElapsed;

	std::vector<IEntity::SCollisionInfo> collisionResultVec = testVerticalCollision(move.y);
	foreach(IEntity::SCollisionInfo collisionInfo, collisionResultVec)
	{
		onTouch(collisionInfo.otherEntity);
	}
	
	setCoord(coord+move);
}

IEntity::CollisionType CDebris::onTouch(boost::shared_ptr<IEntity> other)
{
	if(other->className() == "CHero" )
	{
		boost::shared_ptr<CHero> hero = other->getHandle().to<CHero>();
		if(hero->isActive())
			CGameEngine::instance()->heroDied(hero);
	}
	return KILLHERO;
}