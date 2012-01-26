#include "CClientGameEngine.h"

#include "Event/Network/CClientEventEngine.h"
#include "Event/Network/CClientSession.h"
#include "Event/GameEvent/HeroEvent.h"

#include "Graphics/CRenderEngine.h"
#include "Input/CInputEngine.h"
#include <SFML/Graphics.hpp>
#include "State/CConnectingState.h"
#include "Level/CLevel.h"
#include "Sound/CSoundEngine.h"

#include "Log/CSFMLLog.h"

CClientGameEngine::CClientGameEngine(boost::program_options::variables_map vm) : CGameEngine(false), m_syncTime(0.f)
{
	boost::shared_ptr<CSFMLLog> logger = CSFMLLog::init();

	boost::shared_ptr<CSoundEngine> soundEngine(new CSoundEngine());
	setSoundEngine(soundEngine);

	UInt16 width = vm["width"].as<UInt16>();
	UInt16 height = vm["height"].as<UInt16>();
	getLevel()->setScreenSize(sf::Vector2i(800,height+1));

	boost::shared_ptr<sf::RenderWindow> renderWindow(new sf::RenderWindow(sf::VideoMode(width,height,32),"Tour devel 0.1b"));
	boost::shared_ptr<CRenderEngine> renderEngine = boost::shared_ptr<CRenderEngine>(new CRenderEngine(renderWindow, logger));
	setRenderEngine(renderEngine);
	m_inputEngine = boost::shared_ptr<CInputEngine>(new CInputEngine(renderWindow));

	boost::shared_ptr<CClientSession> session(new CClientSession());
	boost::shared_ptr<CClientEventEngine> eventEngine = boost::shared_ptr<CClientEventEngine>(new CClientEventEngine(session));
	setEventEngine(eventEngine);
	m_clientSession = session;
	m_clientEventEngine = eventEngine;

	std::string host = vm["h"].as<std::string>();
	std::string port = vm["p"].as<std::string>();;

	session->connect(host,port);

	CLog::debug("Client started");
}

Int8 CClientGameEngine::getLocalPlayerId() const
{
	return m_clientEventEngine.lock()->getConnectionID();
}

void CClientGameEngine::update(float elapsedTime)
{
	m_inputEngine->onFrame(elapsedTime);
	getRenderEngine()->onFrame(elapsedTime);

	m_syncTime += elapsedTime;
	if(m_syncTime >= 0.25f)
	{
		boost::shared_ptr<CEvent> syncHero(new CHeroSyncEvent());
		getEventEngine()->newEvent(syncHero);
		m_syncTime = 0;
	}
}

void CClientGameEngine::initEngine()
{
	boost::shared_ptr<CConnectingState> connectingState(new CConnectingState());
	pushState(connectingState);
}

