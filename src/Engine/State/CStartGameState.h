#ifndef CSTARTGAMESTATE_H
#define CSTARTGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "IState.h"

//!état de début de jeu
class CStartGameState : public IState
{
public:
	CStartGameState(const int &initTime);

	void begin();
	void update(const float &elapsedTime);
	void end();

	void handleInput(const sf::Event &event, const sf::Input &input);
private:
	boost::shared_ptr<sf::String> m_decountDrawable;
	boost::shared_ptr<sf::Font> m_font;
	float m_time;
};

#endif

