#include "CGameLostState.h"

#include "../CGameEngine.h"
#include "../Graphics/CRenderEngine.h"

CGameLostState::CGameLostState()
	: m_loseMsgDrawable(new sf::String())//, m_font(new sf::Font())
{
	//m_font->LoadFromFile("data/arial.ttf",72);

	//m_loseMsgDrawable->SetFont(*m_font);
	m_loseMsgDrawable->SetPosition(200.f,150.f);
	m_loseMsgDrawable->SetSize(100.f);
	m_loseMsgDrawable->SetColor(sf::Color::Red);

	m_loseMsgDrawable->SetText("Game Over");
}

void CGameLostState::begin()
{
	boost::shared_ptr<CRenderEngine> renderEngine(CGameEngine::instance()->getRenderEngine());
	if(renderEngine)
		renderEngine->addScreenEffect(m_loseMsgDrawable);
}

void CGameLostState::update(const float &elapsedTime)
{

}

void CGameLostState::end()
{

}

void CGameLostState::handleInput(const sf::Event &event, const sf::Input &input)
{
	if(event.Type == sf::Event::Closed)
		CGameEngine::instance()->stop();
}