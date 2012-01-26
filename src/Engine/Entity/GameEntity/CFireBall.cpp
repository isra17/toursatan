#include "CFireBall.h"
#include "CHero.h"
#include "../../Util.h"

CFireBall::CFireBall(float speed, boost::shared_ptr<IModel> model)
: IEntity(model), m_speed(speed)
{
	getModel()->setAnim("Thrown");
}

//Avance la boule de feu
void CFireBall::update(float timeElapsed)
{
	sf::Vector2f coord = getCoord();
	float move = m_speed * timeElapsed;

	std::vector<IEntity::SCollisionInfo> collisionResultVec = testHorizontalCollision(move);
	foreach(IEntity::SCollisionInfo collisionInfo, collisionResultVec)
	{
		onTouch(collisionInfo.otherEntity);
	}

	coord.x += move;

	sf::FloatRect screenRect = CGameEngine::instance()->getScreenRect();
	if(coord.x < screenRect.Left || coord.x + getDim().x > screenRect.Right)
		CGameEngine::instance()->deleteEntity(getHandle(),true);
	else
		setCoord(coord);
}

//Tue un hero ou detruit la boule de feu
IEntity::CollisionType CFireBall::onTouch(boost::shared_ptr<IEntity> other)
{
	bool destroy = true;
	if(other->className() == "CHero" )
	{
		boost::shared_ptr<CHero> hero = other->getHandle().to<CHero>();
		if(hero->isActive())
			CGameEngine::instance()->heroDied(hero);
		else
			destroy = false;
	}
	else if(other->className() == "CSatan" || other->className() == "CDebris")
		destroy = false;

	if(destroy)
		CGameEngine::instance()->deleteEntity(getHandle(),true);
	return KILLHERO;
}

//Definit la vitesse de la boule de feu
void CFireBall::setSpeed(float speed)
{
	m_speed = speed;
}