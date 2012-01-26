#include "CEventFactory.h"
#include "CEvent.h"

#include "CMsgEvent.h"
#include "GameEvent/HeroEvent.h"
#include "GameEvent/NetworkEvent.h"

#include "EventID.h"

#include <exception>

boost::shared_ptr<CEvent> CEventFactory::build(int id, std::string data)
{
	boost::shared_ptr<CEvent> event_ptr;
	std::istringstream buffer(data, std::ios_base::in | std::ios_base::binary);

	//passe les quatres premier octet
	buffer.seekg(2);
	Int8 from;
	buffer.read((char*)&from,sizeof(Int8));

	if(id == EVENT_MSG)
		event_ptr = boost::shared_ptr<CMsgEvent>(new CMsgEvent(buffer));
	else if(id == EVENT_HEROMOVE)
		event_ptr = boost::shared_ptr<CHeroMoveEvent>(new CHeroMoveEvent(buffer));
	else if(id == EVENT_HEROJUMP)
		event_ptr = boost::shared_ptr<CHeroJumpEvent>(new CHeroJumpEvent(buffer));
	else if(id == EVENT_HEROSYNC)
		event_ptr = boost::shared_ptr<CHeroSyncEvent>(new CHeroSyncEvent(buffer));
	else if(id == EVENT_HEROSTOPJUMP)
		event_ptr = boost::shared_ptr<CHeroStopJumpEvent>(new CHeroStopJumpEvent(buffer));
	else if(id == EVENT_HEROADDSCORE)
		event_ptr = boost::shared_ptr<CHeroAddScore>(new CHeroAddScore(buffer));

	//NetworkEvent
	else if(id == EVENT_NETWORKHELLO)
		event_ptr = boost::shared_ptr<CNetworkHelloEvent>(new CNetworkHelloEvent(buffer));
	else if(id == EVENT_NETWORKSYNCPLAYERDATA)
		event_ptr = boost::shared_ptr<CNetworkSyncPlayerDataEvent>(new CNetworkSyncPlayerDataEvent(buffer));
	else if(id == EVENT_NETWORKSTARTGAME)
		event_ptr = boost::shared_ptr<CNetworkStartGameEvent>(new CNetworkStartGameEvent(buffer));
	else if(id == EVENT_NETWORKCLIENTSTATE)
		event_ptr = boost::shared_ptr<CNetworkClientStateEvent>(new CNetworkClientStateEvent(buffer));
	else
		throw(std::exception("Invalid EventID"));
	
	event_ptr->setSource(from);
	
	return event_ptr;
}