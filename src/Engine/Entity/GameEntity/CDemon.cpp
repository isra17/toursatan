#include "CDemon.h"
#include "CFireBall.h"
#include "CHero.h"
#include "../../Util.h"
#include "../../Resource/CResourceEngine.h"

CDemon::CDemon(float speed, float interval, boost::shared_ptr<IModel> model)
: IEntity(model), m_speed(speed), m_interval(interval), m_elapsedTime(0.f)
{
	if(m_speed > 0)
		getModel()->setAnim("StandRight");
	else
		getModel()->setAnim("StandLeft");
}

//lance des boules de feu a chaque interval de temps
void CDemon::update(float elapsedTime)
{
	m_elapsedTime += elapsedTime;
	if(m_elapsedTime >= m_interval)
	{
		m_elapsedTime -= m_interval;
		shoot();
	}
	
	if(m_elapsedTime >= 0.3f)
	{
		if(m_speed > 0)
			getModel()->setAnim("StandRight");
		else
			getModel()->setAnim("StandLeft");
	}
}

//gère les colision avec les autre entité
IEntity::CollisionType CDemon::onTouch(boost::shared_ptr<IEntity> other)
{
	if(other->className() == "CHero")
	{
		if(other->getCoord().y + other->getDim().y < getCoord().y)
		{
			CGameEngine::instance()->addScore(other,250);
			CGameEngine::instance()->deleteEntity(getHandle(),true);
			other->getHandle().to<CHero>()->bounce(600.f);
		}
	}

	return BLOCK;
}

//Definit la vitesse initial des boules de feu
void CDemon::setInitialSpeed(float speed)
{
	m_speed = speed;
}

float CDemon::getInitialSpeed()
{
	return m_speed;
}

//Definit l'interval des boule de feu
void CDemon::setInterval(float interval)
{
	m_interval = interval;
}

float CDemon::getInterval()
{
	return m_interval;
}

void CDemon::shoot()
{
	if(m_speed > 0)
		getModel()->setAnim("ShootRight");
	else
		getModel()->setAnim("ShootLeft");
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("FireBall"));
	boost::shared_ptr<IEntity> fireBall(new CFireBall(m_speed,model));
	fireBall->setDim(sf::Vector2f(50,50));
	if(m_speed > 0)
		fireBall->setCoord(getCoord()+sf::Vector2f(getDim().x,25.f));
	else
		fireBall->setCoord(getCoord()+sf::Vector2f(-fireBall->getDim().x,25.f));
	CGameEngine::instance()->addEntity(fireBall);
}


