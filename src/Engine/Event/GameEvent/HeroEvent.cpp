#include "HeroEvent.h"
#include "../EventID.h"
#include "../../CPlayer.h"
#include "../../CGameEngine.h"
#include "../../Resource/CResourceEngine.h"
#include "../../Log/CLog.h"


/******************************************************************************
/*								CHeroMove
/******************************************************************************/

CHeroMoveEvent::CHeroMoveEvent(std::istringstream& data) : CEvent(EVENT_HEROMOVE)
{
	data >> m_direction;
}

CHeroMoveEvent::CHeroMoveEvent(CHero::Direction direction) 
: CEvent(EVENT_HEROMOVE), m_direction(direction)
{
	
}

void CHeroMoveEvent::apply() const
{
	CGameEngine::instance()->getPlayer(getSource()).getEntity()->setDirection(static_cast<CHero::Direction>(m_direction));
}

void CHeroMoveEvent::serializeEvent(std::ostringstream& buffer) const
{
	buffer << m_direction;
}

/******************************************************************************
/*								CHeroJumpEvent
/******************************************************************************/

//unserialize l'objet
CHeroJumpEvent::CHeroJumpEvent(std::istringstream& data) : CEvent(EVENT_HEROJUMP)
{

}

CHeroJumpEvent::CHeroJumpEvent() : CEvent(EVENT_HEROJUMP)
{

}

void CHeroJumpEvent::apply() const
{
	boost::shared_ptr<CHero> hero = CGameEngine::instance()->getPlayer(getSource()).getEntity();
	hero->jump();
}

//serialize l'objet
void CHeroJumpEvent::serializeEvent(std::ostringstream& buffer) const
{

}


/******************************************************************************
/*								CHeroStopJumpEvent
/******************************************************************************/

//unserialize l'objet
CHeroStopJumpEvent::CHeroStopJumpEvent(std::istringstream& data) : CEvent(EVENT_HEROSTOPJUMP)
{

}

CHeroStopJumpEvent::CHeroStopJumpEvent() : CEvent(EVENT_HEROSTOPJUMP)
{

}

void CHeroStopJumpEvent::apply() const
{
	CGameEngine::instance()->getPlayer(getSource()).getEntity()->stopJump();
}

//serialize l'objet
void CHeroStopJumpEvent::serializeEvent(std::ostringstream& buffer) const
{

}

/******************************************************************************
/*								CSyncHeroEvent
/******************************************************************************/

//unserialize l'objet
CHeroSyncEvent::CHeroSyncEvent(std::istringstream& data) 
: CEvent(EVENT_HEROSYNC), COORD_ERROR_MARGIN(50)
{
	data.read((char*)&m_dir,sizeof(UInt8));
	data.read((char*)&m_coord.x,sizeof(float));
	data.read((char*)&m_coord.y,sizeof(float));
}

CHeroSyncEvent::CHeroSyncEvent() 
: CEvent(EVENT_HEROSYNC), COORD_ERROR_MARGIN(50)
{
	boost::shared_ptr<CHero> playerHero = CGameEngine::instance()->getPlayer(
		CGameEngine::instance()->getLocalPlayerId()).getEntity();
	m_dir = playerHero->getDirection();
	m_coord = playerHero->getCoord();
}

void CHeroSyncEvent::apply() const
{
	//Sa donne rien de synchroniser un joueur avec lui meme...
	if(getSource() != CGameEngine::instance()->getLocalPlayerId())
	{
		boost::shared_ptr<CHero> playerHero = CGameEngine::instance()->getPlayer(getSource()).getEntity();
		playerHero->setDirection(static_cast<CHero::Direction>(m_dir));

		//test si l'erreur est assez grand pour la corriger
		if(m_coord.x + COORD_ERROR_MARGIN < playerHero->getCoord().x
			|| m_coord.x - COORD_ERROR_MARGIN > playerHero->getCoord().x
			|| m_coord.y + COORD_ERROR_MARGIN < playerHero->getCoord().y
			|| m_coord.y - COORD_ERROR_MARGIN > playerHero->getCoord().y)
		{
			playerHero->setCoord(m_coord);
			CLog::debug("Correction synchro apporte");
		}
	}
}

//serialize l'objet
void CHeroSyncEvent::serializeEvent(std::ostringstream& buffer) const
{
	buffer.write((char*)&m_dir,sizeof(UInt8));
	buffer.write((char*)&m_coord.x,sizeof(float));
	buffer.write((char*)&m_coord.y,sizeof(float));
}


/******************************************************************************
/*								CHeroAddScore
/******************************************************************************/

CHeroAddScore::CHeroAddScore(std::istringstream& data)
: CEvent(EVENT_HEROADDSCORE)
{
	data.read((char*)&m_playerId, sizeof(UInt8));
	data.read((char*)&m_score, sizeof(UInt32));
}

CHeroAddScore::CHeroAddScore(UInt8 playerId, UInt32 score)
: CEvent(EVENT_HEROADDSCORE), m_score(score), m_playerId(playerId)
{

}

void CHeroAddScore::apply() const
{
	CLog::debug("Score up!");
	CGameEngine::instance()->getPlayer(m_playerId).addScore(m_score);
}

void CHeroAddScore::serializeEvent(std::ostringstream& buffer) const
{
	buffer.write((char*)&m_playerId,sizeof(UInt8));
	buffer.write((char*)&m_score,sizeof(UInt32));
}


