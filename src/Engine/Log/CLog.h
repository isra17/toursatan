#ifndef CLOG_H
#define CLOG_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <ostream>

//!Permet de séparer et d'aficher les messages client et serveur
class CLog
{
public:
	static void debug(const std::string& log);
	static void warning(const std::string& log);
	static void error(const std::string& log);
	static void critical(const std::string& log);

protected:
	virtual void doDebug(const std::string& log)=0;
	virtual void doWarning(const std::string& log)=0;
	virtual void doError(const std::string& log)=0;
	virtual void doCritical(const std::string& log)=0;


	CLog(){}
	static void init(boost::shared_ptr<CLog> logger)
	{
		m_instance = logger;
	};
private:
	static boost::shared_ptr<CLog> m_instance;

	CLog(const CLog&);
};

#endif

