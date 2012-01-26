#ifndef CHERO_H
#define CHERO_H

#include "../IEntity.h"

//!L'entité des heros
class CHero : public IEntity
{
public:
	enum Direction
	{
		right=1,
		left=2,
		none=3
	};

	ENTITY(CHero)

	CHero(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!met à jour la position du hero
	virtual void update(float timeElapsed);

	//!gère les colision avec les autre entité
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!fait sauter le hero
	void jump();
	//!Cesse la progression vertical du hero
	void stopJump();

	//!Applique une poussée vertical sur le joueur
	void bounce(float strength);

	//!définit la direction du joueur
	void setDirection(Direction direction);
	//!Retourne la direction du joueur
	Direction getDirection() const;

	//!Return true si le joueur est actif
	bool isActive();
	void setActive(bool isActive);

	void outOfRange();

	//!Définit la vitesse du hero
	void setSpeed(sf::Vector2f speed);
	//!Retourne la vitesse du hero
	sf::Vector2f getSpeed() const;
private:
	//Vitesse du joueur en u/s
	const float SPEED;
	const float GRAVITY;

	Direction m_faceDirection;

	bool m_onGround;
	bool m_isActive;

	sf::Vector2f m_speed;
	sf::Vector2f m_gravity;
};

#endif

