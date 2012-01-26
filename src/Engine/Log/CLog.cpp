#include "CLog.h"

boost::shared_ptr<CLog> CLog::m_instance;

void CLog::debug(const std::string& log)
{
	if(m_instance)
		m_instance->doDebug(log);
}

void CLog::warning(const std::string& log)
{
	if(m_instance)
		m_instance->doWarning(log);
}

void CLog::error(const std::string& log)
{
	if(m_instance)
		m_instance->doError(log);
}

void CLog::critical(const std::string& log)
{
	if(m_instance)
		m_instance->doCritical(log);
}