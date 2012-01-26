#ifndef CDEBRIS_H
#define CDEBRIS_H

#include "../IEntity.h"

//!L'entit� des d�bris
class CDebris : public IEntity
{
public:
	ENTITY(CDebris)

	CDebris(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!met � jour la position du debris
	virtual void update(float timeElapsed);

	//!g�re les colision avec les autre entit�
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);
private:
	//Vitesse du debris en u/s
	const float SPEED;
	//Vecteur de deplacement du debris en u/s
	sf::Vector2f m_speed;
	
};

#endif
