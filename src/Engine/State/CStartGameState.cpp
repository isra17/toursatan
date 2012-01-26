#include "CStartGameState.h"

#include <sstream>
#include "../CGameEngine.h"
#include "../Graphics/CRenderEngine.h"

CStartGameState::CStartGameState(const int &initTime)
	: m_time(static_cast<float>(initTime)+0.9f), m_decountDrawable(new sf::String()), m_font(new sf::Font())
{
	m_font->LoadFromFile("data/arial.ttf",72);

	m_decountDrawable->SetFont(*m_font);
	m_decountDrawable->SetPosition(300.f,150.f);
	m_decountDrawable->SetSize(300.f);
	m_decountDrawable->SetColor(sf::Color::Red);

	std::stringstream buf;
	buf << initTime;

	m_decountDrawable->SetText(buf.str());
}

void CStartGameState::begin()
{
	boost::shared_ptr<CRenderEngine> renderEngine(CGameEngine::instance()->getRenderEngine());
	if(renderEngine)
		renderEngine->addScreenEffect(m_decountDrawable);
}

void CStartGameState::update(const float &elapsedTime)
{
	m_time -= elapsedTime;

	if(m_time < 0)
	{
		CGameEngine::instance()->popState();
		return;
	}

	int time = static_cast<int>(m_time);
	std::stringstream buf;
	buf << time;

	m_decountDrawable->SetText(buf.str());
}

void CStartGameState::end()
{

}

void CStartGameState::handleInput(const sf::Event &event, const sf::Input &input)
{
	if(event.Type == sf::Event::Closed)
		CGameEngine::instance()->stop();
}

