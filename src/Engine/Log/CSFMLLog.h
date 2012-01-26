#ifndef CSFMLLOG_H
#define CSFMLLOG_H

#include "CLog.h"
#include <deque>
#include <boost/shared_ptr.hpp>
#include <sfml/Graphics.hpp>

//!Affiche les messages dans l'écran de jeu
class CSFMLLog : public CLog
{
public:
	static boost::shared_ptr<CSFMLLog> init()
	{
		boost::shared_ptr<CSFMLLog> instance(new CSFMLLog());
		CLog::init(instance);

		return instance;
	};
	void render(boost::shared_ptr<sf::RenderWindow> renderTarget);

private:
	virtual void doDebug(const std::string& log);
	virtual void doWarning(const std::string& log);
	virtual void doError(const std::string& log);
	virtual void doCritical(const std::string& log);

	std::deque<std::string> m_queue;

	CSFMLLog(){};
	CSFMLLog(const CSFMLLog&);
};

#endif