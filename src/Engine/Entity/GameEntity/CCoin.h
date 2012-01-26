#ifndef CCOIN_H
#define CCOIN_H

#include "../IEntity.h"

//!L'entité des pièces d'or
class CCoin : public IEntity
{
public:
	ENTITY(CCoin)

	CCoin(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!gère les colision avec les autre entité
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);
private :
	bool m_isActive;
};

#endif
