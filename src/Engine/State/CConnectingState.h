#ifndef CCONNECTINGSTATE_H
#define CCONNECTINGSTATE_H

#include "CWaitState.h"

//!�tat de connexion
class CConnectingState : public CWaitState
{
public:
	void end();
};

#endif

