#ifndef CSERVERGAMEENGINE_H
#define CSERVERGAMEENGINE_H

#include "CGameEngine.h"
#include <boost/program_options.hpp>

//!Le moteur de jeu du serveur
class CServerGameEngine : public CGameEngine
{
public:
	Int8 getLocalPlayerId() const;
private:	
	virtual void update(float elapsedTime);
	virtual void initEngine();

public:
	static void init(boost::program_options::variables_map vm)
	{
		boost::shared_ptr<CGameEngine> gengine(new CServerGameEngine(vm));
		CGameEngine::init(gengine);
	}
private:
	CServerGameEngine(boost::program_options::variables_map vm);
	CServerGameEngine(const CServerGameEngine&);
};

#endif