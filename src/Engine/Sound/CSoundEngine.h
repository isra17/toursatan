#ifndef CSOUNDENGINE_H
#define CSOUNDENGINE_H

#include <SFML/Audio.hpp>

//!Moteur de son
class CSoundEngine
{
public:
	CSoundEngine();
	
	sf::Music& getMusic();

private:

	sf::Music m_music;
};

#endif

