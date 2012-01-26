#ifndef CPLAYGAMESTATE_H
#define CPLAYGAMESTATE_H

#include "IState.h"

//!état d'une partie en cours
class CPlayGameState : public IState
{
public:
	void begin();
	void update(const float &elapsedTime);
	void end();

	void handleInput(const sf::Event &event, const sf::Input &input);
};

#endif

