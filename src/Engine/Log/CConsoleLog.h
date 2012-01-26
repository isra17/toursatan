#ifndef CCONSOLELOG_H
#define CCONSOLELOG_H

#include "CLog.h"

//!Affiche les messages dans la console
class CConsoleLog : public CLog
{
public:
	static void init()
	{
		boost::shared_ptr<CLog> instance(new CConsoleLog);
		CLog::init(instance);
	};

private:
	virtual void doDebug(const std::string& log);
	virtual void doWarning(const std::string& log);
	virtual void doError(const std::string& log);
	virtual void doCritical(const std::string& log);

	CConsoleLog(){};
	CConsoleLog(const CConsoleLog&);
};

#endif