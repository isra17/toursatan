#ifndef CPOFIN_H
#define CPOFIN_H

#include "../IEntity.h"

//!L'entit� des pofins
class CPofin : public IEntity
{
public:
	ENTITY(CPofin)

	/*!
	*	\param speed Vitesse du Pofin
	**/
	CPofin(float speed, boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!met � jour la position du pofin
	virtual void update(float timeElapsed);

	//!g�re les colision avec les autre entit�
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!Definit la vitesse du pofin
	void setSpeed(float speed = 2.0f);

private:
	//Vitesse du joueur en u/s
	float m_speed;
	bool m_isDead;
};

#endif

