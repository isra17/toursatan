#ifndef CGAMEWONSTATE_H
#define CGAMEWONSTATE_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "IState.h"

//!état d'une partie gagnée
class CGameWonState : public IState
{
public:
	CGameWonState();

	void begin();
	void update(const float &elapsedTime);
	void end();

	void handleInput(const sf::Event &event, const sf::Input &input);
private:
	boost::shared_ptr<sf::String> m_winMsgDrawable;
	boost::shared_ptr<sf::Font> m_font;
};

#endif

