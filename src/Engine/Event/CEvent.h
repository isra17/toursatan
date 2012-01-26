#ifndef CEVENT_H
#define CEVENT_H

#include <boost/shared_ptr.hpp>
#include <sstream>
#include <iostream>

#include "../CGameEngine.h"
#include "../Misc/BasicType.h"


//!Les events sont des messages envoyer au moteur de jeu
class CEvent
{
	const UInt16 m_eventID;
	Int8 m_sourceID;
public :
	CEvent(const UInt16 eventID, const Int8 sourceID=-1) : m_eventID(eventID), m_sourceID(sourceID){}
	
	//!Serialize les informations sur l'events et apelle la méthode abstraite de sérialization
	std::string serialize() const
	{
		std::string strbuf;
		std::ostringstream strstream(std::ios_base::binary);
		strstream.write((char*)&m_eventID,2);		
		strstream.write((char*)&m_sourceID,1);
		serializeEvent(strstream);
		return strstream.str();
	}

	//!Appele avant d'etre envoyer aux clients (execute a partie du thread de jeu)
	//!Retourne false pour ne pas etre envoye au clients
	virtual bool onSend() {return true;}

	virtual bool isValid() const
	{
		return true;
	}

	UInt16 getType() const
	{
		return m_eventID;
	}

	Int8 getSource() const
	{
		return m_sourceID;
	}

	void setSource(Int8 source){
		m_sourceID = source;
	}

	//!Applique l'event au moteur de jeu afin de changer son etat
	virtual void apply() const=0;

protected:
	//!Serialize l'objet dans un flux
	virtual void serializeEvent(std::ostringstream& buffer) const=0;
};

#endif