#include "CSatan.h"
#include "CHero.h"
#include "../../CGameEngine.h"
#include "../../Graphics/CRenderEngine.h"

#include "../../Util.h"

CSatan::CSatan(float speed, boost::shared_ptr<CHero> deadHero, boost::shared_ptr<CSatanModel> model)
: IEntity(), m_speed(speed), m_deadHero(deadHero), m_isTracking(true), m_isDead(false), m_satanModel(model)
{
	//Etant donner que bowser doit toujours etre afficher par dessus les autre objet, on l'utilise comme etant un effet
	boost::shared_ptr<CRenderEngine> renderEngine = CGameEngine::instance()->getRenderEngine();
	if(renderEngine)
		renderEngine->addGameEffect(model);

	model->setActiveHero(false);
	if(deadHero)
	{
		deadHero->getModel()->setAnim("Hurt");
		float y = CGameEngine::instance()->getScreenRect().Bottom;
		setCoord(sf::Vector2f(deadHero->getCoord().x-50,y));
	}
	else
		throw(CTourException("deadHero is ptr null"));
}

//met à jour la position du hero
void CSatan::update(float elapsedTime)
{
	boost::shared_ptr<IEntity> deadHero(m_deadHero.lock());
	if(m_isDead || !deadHero)
		return;

	if(m_isTracking)
	{
		sf::Vector2f coord = getCoord();
		float move = -elapsedTime*m_speed;
		if(coord.y + move <= deadHero->getCoord().y-50)
		{
			deadHero->getModel()->setActive(false);
			m_isTracking = false;
			move = deadHero->getCoord().y - coord.y;
			m_satanModel->setAnim("Hurt");
			m_satanModel->setActiveHero(true);
		}

		setCoord(sf::Vector2f(coord.x, coord.y + move));
		m_satanModel->SetPosition(getCoord());
	}
	else
	{
		float x = getCoord().x;
		float move = elapsedTime*m_speed;
		sf::FloatRect screenRect = CGameEngine::instance()->getScreenRect();

		if(x+move >= screenRect.Right - getDim().x - 50)
		{
			move = screenRect.Right - getDim().x - 50 - x;
			m_speed *= -1.f;
		}
		else if(x+move <= screenRect.Left + 50)
		{
			move = screenRect.Left + 50 - x;
			m_speed *= -1.f;
		}

		float y = CGameEngine::instance()->getScreenRect().Bottom - getDim().y - 50;
		float verMove = y -getCoord().y;

		std::vector<IEntity::SCollisionInfo> collisionResultVec = testVerticalCollision(verMove);
		foreach(IEntity::SCollisionInfo collisionInfo, collisionResultVec)
		{
			onTouch(collisionInfo.otherEntity);
		}

		collisionResultVec.clear();
		collisionResultVec = testHorizontalCollision(move);
		foreach(IEntity::SCollisionInfo collisionInfo, collisionResultVec)
		{
			onTouch(collisionInfo.otherEntity);
		}

		deadHero->setCoord(getCoord() + sf::Vector2f(move+5.f,5.f));

		

		setCoord(sf::Vector2f(getCoord().x + move,y));
		m_satanModel->SetPosition(getCoord());
	}
}

//gère les colision avec les autre entité
IEntity::CollisionType CSatan::onTouch(boost::shared_ptr<IEntity> other)
{
	if(!m_isDead && !m_isTracking)
	{
 		if(other->className() == "CHero")
		{
			boost::shared_ptr<CHero> hero = other->getHandle().to<CHero>();
			if(hero->isActive())
			{
				if(hero->getCoord().y + hero->getDim().y < getCoord().y)
				{
					hero->bounce(1600.f);
					boost::shared_ptr<CHero> deadHero(m_deadHero.lock()->getHandle().to<CHero>());
					if(deadHero)
					{
						deadHero->getModel()->setActive(true);
						deadHero->setActive(true);
						deadHero->bounce(1600.f);
					}
					m_isDead = true;
					
					CGameEngine::instance()->deleteEntity(getHandle(),true);
				}
				else
				{
					CGameEngine::instance()->heroDied(hero);
				}
			}
		}
	}

	return NOTHING;
}