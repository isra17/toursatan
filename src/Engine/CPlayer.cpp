#include "CPlayer.h"
#include "Entity/GameEntity/CHero.h"

CPlayer::CPlayer()
: m_score(0)
{

}

//get/set pour l'entity du joueur
void CPlayer::setEntity(boost::shared_ptr<CHero> entity)
{
	m_entity = entity;
}

boost::shared_ptr<CHero> CPlayer::getEntity() const
{
	return m_entity;
}

void CPlayer::addScore(unsigned int score)
{
	m_score += score;
}

unsigned int CPlayer::getScore() const
{
	return m_score;
}