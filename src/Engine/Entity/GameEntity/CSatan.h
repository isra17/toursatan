#ifndef CSATAN_H
#define CSATAN_H

#include "../IEntity.h"
#include <boost/weak_ptr.hpp>

#include "../../Graphics/Model/CSatanModel.h"

class CHero;

//!L'entit� de Satan(bowser)
class CSatan : public IEntity
{
public:
	ENTITY(CSatan)

	/*!
	*	\param speed Vitesse de Satan
	**/
	CSatan(float speed, boost::shared_ptr<CHero> deadHero, boost::shared_ptr<CSatanModel> model);

	//!met � jour la position de satan
	virtual void update(float timeElapsed);

	//!g�re les colision avec les autre entit�
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!va chercher un joueur
	void grabHero(boost::shared_ptr<CHero> hero);

private:
	boost::weak_ptr<CHero> m_deadHero;
	float m_speed;
	bool m_isTracking;
	bool m_isDead;

	boost::shared_ptr<CSatanModel> m_satanModel;
};

#endif

