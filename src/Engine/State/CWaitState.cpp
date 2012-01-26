#include "CWaitState.h"

#include "../CGameEngine.h"

void CWaitState::begin()
{

}

void CWaitState::update(const float &elapsedTime)
{

}

void CWaitState::end()
{
	
}

void CWaitState::handleInput(const sf::Event &event, const sf::Input &input)
{
	if(event.Type == sf::Event::Closed)
		CGameEngine::instance()->stop();
}


