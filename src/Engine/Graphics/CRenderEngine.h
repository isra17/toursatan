#ifndef CRENDERENGINE_H
#define CRENDERENGINE_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>

#include "../Log/CSFMLLog.h"

//!Moteur graphique
class CRenderEngine
{
    public:
		CRenderEngine(boost::shared_ptr<sf::RenderWindow> renderTarget, boost::weak_ptr<CSFMLLog> logger);
        virtual ~CRenderEngine();

        virtual void onFrame(float m_lastFrame);

		void addGameEffect(boost::shared_ptr<sf::Drawable> effect);
		void addScreenEffect(boost::shared_ptr<sf::Drawable> effect);

    private:
		//!Affiche le fps sur l'écran
		void renderFPS();
		//!Affiche l'interface de l'utilisateur
		void renderUI();

		int m_nbFrame;
		float m_timerFPS;
		float m_gameTime;
		sf::String m_FPS;
		sf::String m_text;
		boost::shared_ptr<sf::RenderWindow> m_renderTarget;
		boost::weak_ptr<CSFMLLog> m_logger;

		std::vector<boost::weak_ptr<sf::Drawable> > m_gameEffects;
		std::vector<boost::weak_ptr<sf::Drawable> > m_screenEffects;
};

#endif // HW_RENDERENGINE_H
