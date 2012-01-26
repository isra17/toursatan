#include "CPlayGameState.h"

#include "../CGameEngine.h"
#include "../CPlayer.h"
#include "../Entity/GameEntity/CHero.h"

#include "../Event/GameEvent/HeroEvent.h"
#include "../Event/CEventEngine.h"

#include "../Log/CLog.h"

void CPlayGameState::begin()
{
	
}


void CPlayGameState::update(const float &elapsedTime)
{
	if(elapsedTime > 0)
		CGameEngine::instance()->updateEntity(elapsedTime);
}


void CPlayGameState::end()
{

}

void CPlayGameState::handleInput(const sf::Event &event, const sf::Input &input)
{
	switch(event.Type)
		{
		case sf::Event::KeyPressed:
			switch(event.Key.Code)
			{
			case sf::Key::A:
				{
					boost::shared_ptr<CHeroMoveEvent> moveEvent(new CHeroMoveEvent(CHero::left));
					CGameEngine::instance()->getEventEngine()->newEvent(moveEvent);
				}
				break;
			case sf::Key::D:
				{
					boost::shared_ptr<CHeroMoveEvent> moveEvent(new CHeroMoveEvent(CHero::right));
					CGameEngine::instance()->getEventEngine()->newEvent(moveEvent);
				}
				break;
			case sf::Key::Space:
				{
					boost::shared_ptr<CHeroJumpEvent> jumpEvent(new CHeroJumpEvent());
					CGameEngine::instance()->getEventEngine()->newEvent(jumpEvent);
				}
				break;
			}
			break;

		case sf::Event::KeyReleased:
			{
				switch(event.Key.Code)
				{
				case sf::Key::A:
					{
						CLog::debug("key released");
						CHero::Direction dir = CHero::none;
						if(input.IsKeyDown(sf::Key::D))
							dir = CHero::right;
						boost::shared_ptr<CHeroMoveEvent> moveEvent(new CHeroMoveEvent(dir));
						CGameEngine::instance()->getEventEngine()->newEvent(moveEvent);
					}
					break;
				case sf::Key::D:
					{
						CHero::Direction dir = CHero::none;
						if(input.IsKeyDown(sf::Key::A))
							dir = CHero::left;
						boost::shared_ptr<CHeroMoveEvent> moveEvent(new CHeroMoveEvent(dir));
						CGameEngine::instance()->getEventEngine()->newEvent(moveEvent);
					}
					break;
				case sf::Key::Space:
					{
						boost::shared_ptr<CHeroStopJumpEvent> stopJumpEvent(new CHeroStopJumpEvent());
						CGameEngine::instance()->getEventEngine()->newEvent(stopJumpEvent);
					}
				break;
				}
			}
			break;
		case sf::Event::Closed:
			CGameEngine::instance()->stop();
			break;

		}
}

