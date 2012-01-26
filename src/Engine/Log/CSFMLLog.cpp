#include "CSFMLLog.h"

#include <iostream>
using namespace std;

void CSFMLLog::doDebug(const std::string& log)
{
	m_queue.push_front(log);
}

void CSFMLLog::doWarning(const std::string& log)
{
	m_queue.push_front(log);
}

void CSFMLLog::doError(const std::string& log)
{
	m_queue.push_front(log);
}

void CSFMLLog::doCritical(const std::string& log)
{
	m_queue.push_front(log);
}

void CSFMLLog::render(boost::shared_ptr<sf::RenderWindow> renderTarget)
{
	sf::String text;

	for(size_t i = 0; i < m_queue.size() && i < 5; i++)
	{
		text.SetText(m_queue[i]);
		text.SetFont(sf::Font::GetDefaultFont());
		text.SetSize(15);
		text.SetPosition(0.f, (4.f-i)*text.GetSize());
		text.SetColor(sf::Color::Black);

		renderTarget->Draw(text);
	}
}