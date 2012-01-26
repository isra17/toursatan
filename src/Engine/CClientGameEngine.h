#ifndef CCLIENTGAMEENGINE_H
#define CCLIENTGAMEENGINE_H

#include <boost/weak_ptr.hpp>
#include <boost/program_options.hpp>

#include "CGameEngine.h"
#include "./Log/CSFMLLog.h"

class CRenderEngine;
class CInputEngine;
class CClientEventEngine;
class CClientSession;

//!Le moteur de jeu du client
class CClientGameEngine : public CGameEngine
{
public:
	Int8 getLocalPlayerId() const;

private:
	boost::shared_ptr<CInputEngine> m_inputEngine;
	boost::weak_ptr<CClientEventEngine> m_clientEventEngine;
	boost::weak_ptr<CClientSession> m_clientSession;

	float m_syncTime;
	
	virtual void update(float elapsedTime);
	virtual void initEngine();


public:
	static void init(boost::program_options::variables_map vm)
	{
		boost::shared_ptr<CGameEngine> gengine(new CClientGameEngine(vm));
		CGameEngine::init(gengine);
	}
private:
	CClientGameEngine(boost::program_options::variables_map vm);
	CClientGameEngine(const CClientGameEngine&);
};

#endif