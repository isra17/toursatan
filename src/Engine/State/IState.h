#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Window.hpp>

//!Définit un état de jeu
class IState
{
public:
	virtual void begin()=0;
	virtual void update(const float &elapsedTime)=0;
	virtual void end()=0;

	virtual void handleInput(const sf::Event &event, const sf::Input &input)=0;
};

#endif

