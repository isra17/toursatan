#include "CCoin.h"

CCoin::CCoin(boost::shared_ptr<IModel> model)
: IEntity(model), m_isActive(true)
{

}

//gère les colision avec les autre entité
IEntity::CollisionType CCoin::onTouch(boost::shared_ptr<IEntity> other)
{
	if(m_isActive && other->className() == "CHero")
	{
		m_isActive = false;
		CGameEngine::instance()->addScore(other,100);
		CGameEngine::instance()->deleteEntity(getHandle(),true);
	}

	return NOTHING;
}

