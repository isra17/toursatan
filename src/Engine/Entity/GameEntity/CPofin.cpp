#include "CPofin.h"
#include "CHero.h"

#include "../../Util.h"

CPofin::CPofin(float speed, boost::shared_ptr<IModel> model) 
: IEntity(model), m_speed(speed),m_isDead(false)
{
	getModel()->setAnim("RunLeft");
}

void CPofin::update(float timeElapsed)
{
	sf::Vector2f coord = getCoord();
	sf::Vector2f move;
	move.x = m_speed * timeElapsed;
	move.y = 1;

	std::vector<IEntity::SCollisionInfo> collisionResultVec = testHorizontalCollision(move.x);
	foreach(IEntity::SCollisionInfo collisionResult, collisionResultVec)
	{
		if(collisionResult.otherEntity->onTouch(shared_from_this()) == BLOCK
			&& abs(move.x) > abs(collisionResult.validMove))
		{
			move.x = collisionResult.validMove;
			m_speed *= -1;
		}
	}

	//Deplace le Pofin Lateralement
	setCoord(coord+sf::Vector2f((m_speed < 0 ? move.x - 50 : move.x + 50),0));

	collisionResultVec.clear();
	collisionResultVec = testVerticalCollision(move.y);

	if(collisionResultVec.empty())
		m_speed *= -1;
	else
	{
		bool isBlock = false;
		foreach(IEntity::SCollisionInfo collisionResult, collisionResultVec)
		{
			if(collisionResult.otherEntity->onTouch(shared_from_this()) == BLOCK)
				isBlock = true;
		}
		if(!isBlock)
			m_speed *= -1;
	}

	if(m_speed > 0)
		getModel()->setAnim("RunRight");
	else
		getModel()->setAnim("RunLeft");

	setCoord(coord+sf::Vector2f(move.x,0));
}

IEntity::CollisionType CPofin::onTouch(boost::shared_ptr<IEntity> other)
{
	if(other->className() == "CHero")
	{
		boost::shared_ptr<CHero> hero = other->getHandle().to<CHero>();
		if(hero->isActive())
		{
 			if(other->getCoord().y + other->getDim().y <= getCoord().y)
			{
				hero->bounce(600.f);
				CGameEngine::instance()->addScore(other,250);
				CGameEngine::instance()->deleteEntity(getHandle(),true);
				m_isDead = true;
			}
			else if(!m_isDead)
				CGameEngine::instance()->heroDied(hero);
		}
	}
		
	return KILLHERO;
}

//Definit la vitesse du pofin
void CPofin::setSpeed(float speed)
{
	m_speed = speed;
}