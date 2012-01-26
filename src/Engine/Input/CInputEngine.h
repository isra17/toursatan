#ifndef CINPUTENGINE_H
#define CINPUTENGINE_H

#include <SFML/Window.hpp>
#include <boost/shared_ptr.hpp>

//!Moteur d'entré
class CInputEngine
{
    public:
		CInputEngine(boost::shared_ptr<sf::Window> window);

		//Handle events from input (mouse/keyboard)
        virtual void onFrame(float m_lastFrame);
    private:
		boost::shared_ptr<sf::Window> m_window;
};

#endif // CHU_CINPUTENGINE_H
