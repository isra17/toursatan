#include "CRenderEngine.h"
#include "../Entity/CEntityList.h"
#include "../Util.h"
#include "../Log/CSFMLLog.h"
#include "../Level/CLevel.h"

#include <sstream>
#include <iomanip>

CRenderEngine::CRenderEngine(boost::shared_ptr<sf::RenderWindow> renderTarget,
	boost::weak_ptr<CSFMLLog> logger) : m_renderTarget(renderTarget),
	m_logger(logger),m_nbFrame(0), m_timerFPS(0), m_gameTime(0), m_text("",sf::Font::GetDefaultFont(), 15)
{
	m_FPS.SetPosition(0, (float)m_renderTarget->GetHeight()-40);
	m_FPS.SetColor(sf::Color::Black);
	m_text.SetSize(40);
	m_text.SetColor(sf::Color::Black);
}

CRenderEngine::~CRenderEngine()
{
}

void CRenderEngine::onFrame(float m_lastFrame)
{
	m_gameTime += m_lastFrame;
    m_renderTarget->Clear();

	//Affiche le fond du jeu
	m_renderTarget->Draw(*CGameEngine::instance()->getLevel()->getBackgroundSprite());

	//Recupere les entity a afficher
	boost::shared_ptr<CEntityList> entityList = CGameEngine::instance()->getEntityList();
	sf::FloatRect screenRect = CGameEngine::instance()->getScreenRect();

	for(CEntityList::constitEntity i=entityList->begin();i!=entityList->end();i++)
	{
		boost::shared_ptr<IEntity> entity = i->second;
		if(entity)
		{
			boost::shared_ptr<IModel> drawable = entity->getModel();
			drawable->SetPosition(entity->getCoord().x,entity->getCoord().y - screenRect.Bottom + screenRect.GetHeight());
			m_renderTarget->Draw(*drawable);
		}
		else
			throw(CTourException("Attempt to render null ptr entity"));
	}

	foreach(boost::weak_ptr<sf::Drawable> effect, m_gameEffects)
	{
		boost::shared_ptr<sf::Drawable> ptrEffect = effect.lock();
		if(ptrEffect)
		{
			const sf::Vector2f coord = ptrEffect->GetPosition();
			ptrEffect->SetPosition(coord.x,coord.y - screenRect.Bottom + screenRect.GetHeight());
			m_renderTarget->Draw(*ptrEffect);
			ptrEffect->SetPosition(coord);
		}
	}

	foreach(boost::weak_ptr<sf::Drawable> effect, m_screenEffects)
	{
		boost::shared_ptr<sf::Drawable> ptrEffect = effect.lock();
		if(ptrEffect)
			m_renderTarget->Draw(*ptrEffect);
	}


	boost::shared_ptr<CSFMLLog> SFMLlogger = m_logger.lock();
	if(SFMLlogger)
		SFMLlogger->render(m_renderTarget);

	renderFPS();
	renderUI();

	m_renderTarget->Display();
}

void CRenderEngine::renderFPS()
{
	m_nbFrame++;
	m_timerFPS += m_renderTarget->GetFrameTime();

	if(m_timerFPS >= 1.f)
	{
		std::stringstream out;
		out << m_nbFrame/m_timerFPS;
		m_FPS.SetText(out.str());
		m_nbFrame = 0;
		m_timerFPS = 0;
	}

	m_renderTarget->Draw(m_FPS);
}

void CRenderEngine::renderUI()
{
	const std::map<Int8, CPlayer>& players = CGameEngine::instance()->getPlayerList();
	sf::Sprite borderSprite(*CGameEngine::instance()->getLevel()->getBorderSprite());
	sf::FloatRect screenRect = CGameEngine::instance()->getScreenRect();

	borderSprite.SetPosition(screenRect.GetWidth(), 0);
	m_renderTarget->Draw(borderSprite);

	m_text.SetText("Chrono");
	m_text.SetPosition(screenRect.GetWidth()+50, 15);
	m_renderTarget->Draw(m_text);
	
	m_text.SetText("Joueur 1");
	m_text.SetPosition(screenRect.GetWidth()+40, screenRect.GetHeight()/3);
	m_renderTarget->Draw(m_text);

	m_text.SetText("Joueur 2");
	m_text.SetPosition(screenRect.GetWidth()+40, screenRect.GetHeight()/3 * 2);
	m_renderTarget->Draw(m_text);

	m_text.SetSize(20);

	std::ostringstream conversion;
	int strOffset = 0;
	conversion << (int)m_gameTime;

	m_text.SetText(conversion.str());
	strOffset = 112 - ((conversion.str().length()-1) * m_text.GetSize()/3);
	m_text.SetPosition(screenRect.GetWidth()+strOffset, 75);
	m_renderTarget->Draw(m_text);

	std::map<Int8, CPlayer>::const_iterator itPlayer;

	for(itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
	{
		std::ostringstream scoreConversion;
		scoreConversion << itPlayer->second.getScore();
		strOffset = 112 - ((scoreConversion.str().length()-1) * m_text.GetSize()/3 );
		m_text.SetText(scoreConversion.str());
		switch(itPlayer->first)
		{
			case 1:				
				m_text.SetPosition(screenRect.GetWidth()+strOffset, screenRect.GetHeight()/3 + 75);				
				break;
			case 2:
				m_text.SetPosition(screenRect.GetWidth()+strOffset, (screenRect.GetHeight()/3 * 2) + 75);
				break;
		}
		m_renderTarget->Draw(m_text);
	}

	m_text.SetSize(40);
}


void CRenderEngine::addGameEffect(boost::shared_ptr<sf::Drawable> effect)
{
	m_gameEffects.push_back(effect);
}

void CRenderEngine::addScreenEffect(boost::shared_ptr<sf::Drawable> effect)
{
	m_screenEffects.push_back(effect);
}

