#include "CGameWonState.h"

#include "../CGameEngine.h"
#include "../Graphics/CRenderEngine.h"

CGameWonState::CGameWonState()
	: m_winMsgDrawable(new sf::String()), m_font(new sf::Font())
{
	m_font->LoadFromFile("data/arial.ttf",72);

	m_winMsgDrawable->SetFont(*m_font);
	m_winMsgDrawable->SetPosition(200.f,150.f);
	m_winMsgDrawable->SetSize(100.f);
	m_winMsgDrawable->SetColor(sf::Color::Red);

	m_winMsgDrawable->SetText("You Win!");
}

void CGameWonState::begin()
{
	boost::shared_ptr<CRenderEngine> renderEngine(CGameEngine::instance()->getRenderEngine());
	if(renderEngine)
		renderEngine->addScreenEffect(m_winMsgDrawable);
}

void CGameWonState::update(const float &elapsedTime)
{

}

void CGameWonState::end()
{

}

void CGameWonState::handleInput(const sf::Event &event, const sf::Input &input)
{
	if(event.Type == sf::Event::Closed)
		CGameEngine::instance()->stop();
}

