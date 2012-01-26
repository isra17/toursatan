#include "CAnim.h"


CAnim::CAnim(void) : m_time()
{
	//Initialise les attributs
	m_frameCount=0;
	m_delay=0.f;
	m_isLoop=true;
	m_play=true;
}

CAnim::~CAnim(void)
{
}

void CAnim::nextFrame()
{
	//Si c'est le dernier frame, on recommence au premier 
	//si le mode boucle est acliver (isLoop)
	//sinon on remet passe au suivant
	if(currentFrame()==getSize()-1)
	{
			setFrame(0);
			if(!isLoop())
				stop();
	}
	else
		setFrame(currentFrame()+1);
}

void CAnim::setFrame(const unsigned int &count)
{
	//s'assurce que le frame existe sinon, met le premier par defaut
	if(count<getSize())
		m_frameCount=count;
	else
		m_frameCount=0;
}

void CAnim::reset()
{
	stop();
	play();
}

void CAnim::loop(const bool &choice)
{
	m_isLoop=choice;
}

void CAnim::play()
{
	m_play = true;
	m_time.play();
}

void CAnim::stop()
{
	//arrete l'CAnimation, remet le premier frame et met le timer a 0
	m_play = false;
	setFrame(0);
	m_time.stop();
}

void CAnim::pause()
{
	m_play = false;
	m_time.pause();
}

bool CAnim::isPlaying() const
{
	return m_play;
}

void CAnim::setDelay(const float &delay)
{
	m_delay=delay;
}

float CAnim::delay() const
{
	return m_delay;
}

unsigned int CAnim::currentFrame() const
{
	return m_frameCount;
}

bool CAnim::isLoop() const
{
	return m_isLoop;
}

void CAnim::update()
{
	if(isPlaying())
	{
		//S'assure que le delay n'est pas 0 sinon il y a une division par 0
		//lorsque le framecount est calculer
		if(delay())
		{
			unsigned int frameCount = (unsigned int)(m_time.getTick()/delay());
			//Si l'animation n'est pas en boucle, on l'arrete a sa fin
			if(!isLoop() && frameCount>getSize())
				stop();
			//sinon on met le frame adapter selon le temps present
			else
			{
				frameCount = frameCount % getSize();
				setFrame(frameCount);
			}
		}
		else nextFrame();
	}
}

