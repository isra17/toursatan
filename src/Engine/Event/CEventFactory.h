#ifndef CEVENTFACTORY_H
#define CEVENTFACTORY_H

#include <boost/shared_ptr.hpp>

class CEvent;

//!Crée des events selon l'ID du type et un buffer
class CEventFactory
{
public :
	static boost::shared_ptr<CEvent> build(int id, std::string data);
};

#endif