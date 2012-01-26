#include "CHero.h"
#include "../../Util.h"
#include "../../Level/CLevel.h"

CHero::CHero(boost::shared_ptr<IModel> model) 
: IEntity(model), SPEED(500.f), GRAVITY(3200.f), m_onGround(true), m_isActive(true)
{
	model->setAnim("StandRight");
}

void CHero::update(float timeElapsed)
{
	if(m_isActive)
	{
		m_speed.y += GRAVITY*timeElapsed;
		if(m_speed.y > 1000)m_speed.y=1000;

		sf::Vector2f coord = getCoord();
		sf::Vector2f move = m_speed;
		move *= timeElapsed;

		sf::FloatRect screenRect = CGameEngine::instance()->getScreenRect();
		
		//Deplace le Hero Lateralement
		std::vector<IEntity::SCollisionInfo> collisionResultVec = testHorizontalCollision(move.x);
		foreach(IEntity::SCollisionInfo collisionResult, collisionResultVec)
		{
			if(collisionResult.otherEntity->onTouch(shared_from_this()) == BLOCK
				&& abs(move.x) > abs(collisionResult.validMove))
				move.x = collisionResult.validMove;
		}

		if(coord.x + move.x < screenRect.Left)
			move.x = -coord.x;
		else if(coord.x + getDim().x + move.x > screenRect.Right)
			move.x = screenRect.Right - (coord.x + getDim().x);

		setCoord(coord+sf::Vector2f(move.x,0));

		//Deplace le Hero verticalement
		collisionResultVec.clear();
		collisionResultVec = testVerticalCollision(move.y);
		foreach(IEntity::SCollisionInfo collisionResult, collisionResultVec)
		{
			if(collisionResult.otherEntity->onTouch(shared_from_this()) == BLOCK
				&& abs(move.y) > abs(collisionResult.validMove))
				move.y = collisionResult.validMove;
		}

		if(move.y == 0 && m_speed.y < 0)
			m_speed.y = 0;

		if(move.y == 0 && m_speed.y > 0)
		{
			if(!m_onGround)
			{
				if(m_speed.x != 0)
				{
					if(m_faceDirection == left)
						getModel()->setAnim("RunLeft");
					else if(m_faceDirection == right)
						getModel()->setAnim("RunRight");
				}
				else
				{
					if(m_faceDirection == left)
						getModel()->setAnim("StandLeft");
					else if(m_faceDirection == right)
						getModel()->setAnim("StandRight");
				}
			}
			m_onGround = true;
			m_speed.y = 0;
		}
		else
			m_onGround = false;

		setCoord(coord+move);
	
		if(getCoord().y + getDim().y <= CGameEngine::instance()->getLevel()->getEndLevel() && CGameEngine::instance()->getLevel()->isEndReached())
		{
			CGameEngine::instance()->addScore(shared_from_this(),500);
			CGameEngine::instance()->winGame();
		}
		else if(getCoord().y > screenRect.Bottom)
 			CGameEngine::instance()->heroDied(boost::shared_dynamic_cast<CHero>(shared_from_this()));
	
	}
}

IEntity::CollisionType CHero::onTouch(boost::shared_ptr<IEntity> other)
{
	return NOTHING;
}

//fait sauter le hero
void CHero::jump()
{
	if(isActive())
	{
		if(m_onGround)
		{
			if(m_faceDirection == left)
				getModel()->setAnim("JumpLeft");
			else if(m_faceDirection == right)
				getModel()->setAnim("JumpRight");

			m_speed.y = -1200.f;
		}
	}
}

void CHero::stopJump()
{
	if(m_speed.y < 0)
		m_speed.y = 0;
}

//Applique une poussée vertical sur le joueur
void CHero::bounce(float strength)
{
	m_speed.y = -strength;
}

//définit la direction du joueur
void CHero::setDirection(Direction direction)
{
	if(isActive())
	{
		switch(direction)
		{
			case right:
				if(m_onGround)
					getModel()->setAnim("RunRight");
				else
					getModel()->setAnim("JumpRight");

				m_faceDirection = right;
				m_speed.x = SPEED;
				break;
			case left:
				if(m_onGround)
					getModel()->setAnim("RunLeft");
				else
					getModel()->setAnim("JumpLeft");

				m_faceDirection = left;
				m_speed.x = -SPEED;
				break;
			case none:
				if(m_onGround)
				{
					if(m_faceDirection == left)
						getModel()->setAnim("StandLeft");
					else if(m_faceDirection == right)
						getModel()->setAnim("StandRight");
				}

				m_speed.x = 0.f;
				break;
		}
	}
}

CHero::Direction CHero::getDirection() const
{
	return m_speed.x > 0? right : (m_speed.x < 0?left : none);
}


bool CHero::isActive()
{
	return m_isActive;
}

void CHero::setActive(bool isActive)
{
	m_isActive = isActive;
}

void CHero::outOfRange()
{
	;
}


//set/get de la vitesse du hero
void CHero::setSpeed(sf::Vector2f speed)
{
	m_speed = speed;
}

sf::Vector2f CHero::getSpeed() const
{
	return m_speed;
}

