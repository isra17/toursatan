#include "CClock.h"

CClock::CClock() : m_isRunning(true)
{
    reset();
}

float CClock::getTick()
{
	if(m_isRunning)
		return m_clock.GetElapsedTime() - m_delay;
	else
		return m_stopTick;
}

void CClock::pause()
{
    if(m_isRunning)
    {
        m_isRunning = false;
        m_stopTick = m_clock.GetElapsedTime();
    }
}

void CClock::play()
{
    if(!m_isRunning)
    {
        m_delay += m_clock.GetElapsedTime() - m_stopTick;
        m_isRunning = true;
    }
}

void CClock::stop()
{
    pause();
    reset();
}

void CClock::toggle()
{
    m_isRunning ? pause() : play();
}

void CClock::reset()
{
    m_clock.Reset();
    m_delay=0.0f;
    m_stopTick=0.0f;
}

bool CClock::isRunning()
{
	return m_isRunning;
}
