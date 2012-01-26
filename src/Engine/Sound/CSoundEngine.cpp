#include "CSoundEngine.h"
#include "../Log/CLog.h"

CSoundEngine::CSoundEngine()
{
	if(!m_music.OpenFromFile("data\\sound\\music.ogg"))
	{
		CLog::debug("Impossible d'ouvrir le fichier de musique");
	}
}
	
sf::Music& CSoundEngine::getMusic()
{
	return m_music;
}

