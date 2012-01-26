#ifndef CDEMON_H
#define CDEMON_H

#include "../IEntity.h"

//!L'entité des démons
class CDemon : public IEntity
{
public:

	ENTITY(CDemon)

	/*!
	*	\param speed	Vitesse initial des boules de feu
	*	\param interval	Interval en seconde entre les boules de feu
	**/
	CDemon(float speed, float interval, boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!lance des boules de feu a chaque interval de temps
	virtual void update(float timeElapsed);

	//!gère les colision avec les autre entité
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!Definit la vitesse initial des boules de feu
	void setInitialSpeed(float speed);
	//!Retourne la vitesse initial des boules de feu
	float getInitialSpeed();

	//!Definit l'interval des boule de feu
	void setInterval(float interval);
	//!Retourne l'interval des boule de feu
	float getInterval();

	//Tire une boule de feu
	void shoot();
private:
	float m_speed;
	float m_interval;

	float m_elapsedTime;
};

#endif

