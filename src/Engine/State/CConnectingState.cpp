#include "CConnectingState.h"

#include "../CGameEngine.h"
#include "../Event/GameEvent/NetworkEvent.h"
#include "../Event/CEventEngine.h"


void CConnectingState::end()
{
	//Le jeu est charge et pret a commencer
	boost::shared_ptr<CNetworkClientStateEvent> event(new CNetworkClientStateEvent(GAMELOADED));
	CGameEngine::instance()->getEventEngine()->newEvent(event);
}
