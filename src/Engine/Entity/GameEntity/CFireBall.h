#ifndef CFIREBALL_H
#define CFIREBALL_H

#include "../IEntity.h"

//!L'entité des boules de feu
class CFireBall : public IEntity
{
public :
	ENTITY(CFireBall)

	/*!
	*	\param speed vitesse de la boule de feu
	**/
	CFireBall(float speed, boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!Avance la boule de feu
	virtual void update(float timeElapsed);

	//!Tue un hero ou detruit la boule de feu
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!Definit la vitesse de la boule de feu
	void setSpeed(float speed = 0.5f);

private:
	float m_speed;
};

#endif

