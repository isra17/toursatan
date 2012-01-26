#ifndef CPLAYER_H
#define CPLAYER_H

#include <boost/shared_ptr.hpp>

class CHero;

//!Définit un joueur
class CPlayer
{
public:
	CPlayer();

	//!get/set pour l'entity du joueur
	void setEntity(boost::shared_ptr<CHero> entity);
	boost::shared_ptr<CHero> getEntity() const;

	//!get/set score
	void addScore(unsigned int score);
	unsigned int getScore() const;
private:
	boost::shared_ptr<CHero> m_entity;
	unsigned int m_score;
};

#endif

