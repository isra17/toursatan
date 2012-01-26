#include "CInputEngine.h"
#include "../CGameEngine.h"


#include "../State/IState.h"

CInputEngine::CInputEngine(boost::shared_ptr<sf::Window> window)
: m_window(window)
{

}

void CInputEngine::onFrame(float m_lastFrame)
{
	sf::Event event;
	const sf::Input& input = m_window->GetInput();
	while(m_window->GetEvent(event))
	{
		CGameEngine::instance()->topState()->handleInput(event,input);
	}
}