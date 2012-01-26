#include "CServerGameEngine.h"

#include "Event/Network/CServerEventEngine.h"
#include "Event/Network/CServerSession.h"

#include "Level/CLevel.h"

#include "Log/CConsoleLog.h"


CServerGameEngine::CServerGameEngine(boost::program_options::variables_map vm) : CGameEngine(true)
{
	CConsoleLog::init();
	
	UInt16 width = vm["width"].as<UInt16>();
	UInt16 height = vm["height"].as<UInt16>();
	getLevel()->setScreenSize(sf::Vector2i(800,height+1));

	std::string port = vm["p"].as<std::string>();
	UInt8 clientCount = static_cast<UInt8>(vm["n"].as<UInt16>());

	boost::shared_ptr<CServerSession> session(new CServerSession(atoi(port.c_str()),clientCount) );
	boost::shared_ptr<CEventEngine> eventEngine = boost::shared_ptr<CEventEngine>(new CServerEventEngine(session));		
	setEventEngine(eventEngine);

	session->listen();

	CLog::debug("Server started");
}

Int8 CServerGameEngine::getLocalPlayerId() const
{
	return -1;
}

void CServerGameEngine::update(float elapsedTime)
{

}

void CServerGameEngine::initEngine()
{
}


