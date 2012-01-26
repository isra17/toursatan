#ifndef CCOIN_H
#define CCOIN_H

#include "../IEntity.h"

//!L'entit� des pi�ces d'or
class CCoin : public IEntity
{
public:
	ENTITY(CCoin)

	CCoin(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!g�re les colision avec les autre entit�
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);
private :
	bool m_isActive;
};

#endif
