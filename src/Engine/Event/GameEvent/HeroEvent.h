#ifndef HEROEVENT_H
#define HEROEVENT_H

#include "../CEvent.h"
#include "../../Entity/GameEntity/CHero.h"

//!Deplace un joueur
class CHeroMoveEvent : public CEvent
{
	public :
	//!unserialize l'objet
	CHeroMoveEvent(std::istringstream& data);

	CHeroMoveEvent(CHero::Direction dir);

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;
private:
	UInt8 m_direction;
};

//!Fait sauter un joueur
class CHeroJumpEvent : public CEvent
{
public :
	//!unserialize l'objet
	CHeroJumpEvent(std::istringstream& data);

	CHeroJumpEvent();

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;
private:
};

//!Arrete le saut d'un joueur
class CHeroStopJumpEvent : public CEvent
{
public :
	//!unserialize l'objet
	CHeroStopJumpEvent(std::istringstream& data);

	CHeroStopJumpEvent();

	virtual void apply() const;
protected :

	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;
private:
};


//!Synchronise l'etat d'un hero
class CHeroSyncEvent : public CEvent
{
public:
	//!unserialize l'objet
	CHeroSyncEvent(std::istringstream& data);

	CHeroSyncEvent();

	virtual void apply() const;
private:
	//!serialize l'objet
	virtual void serializeEvent(std::ostringstream& buffer) const;

	UInt8 m_dir;
	sf::Vector2f m_coord;

	const float COORD_ERROR_MARGIN;
};

//!Ajoute des points au score d'un joueur
class CHeroAddScore : public CEvent
{
public:
	CHeroAddScore(std::istringstream& data);
	CHeroAddScore(UInt8 playerId, UInt32 score);

	void apply() const;
private:
	void serializeEvent(std::ostringstream& buffer) const;

	UInt32 m_score;
	UInt8 m_playerId;
};

#endif

