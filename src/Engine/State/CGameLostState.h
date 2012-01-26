#ifndef CGAMELOSTSTATE_H
#define CGAMELOSTSTATE_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "IState.h"

//!état d'une partie perdue
class CGameLostState : public IState
{
public:
	CGameLostState();

	void begin();
	void update(const float &elapsedTime);
	void end();

	void handleInput(const sf::Event &event, const sf::Input &input);

private:
	boost::shared_ptr<sf::String> m_loseMsgDrawable;
	//boost::shared_ptr<sf::Font> m_font;
};

#endif

