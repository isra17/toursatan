#ifndef CWAITSTATE_H
#define CWAITSTATE_H

#include "IState.h"

//!�tat d'attente
class CWaitState : public IState
{
public:
	virtual void begin();
	virtual void update(const float &elapsedTime);
	virtual void end();

	virtual void handleInput(const sf::Event &event, const sf::Input &input);
};

#endif

