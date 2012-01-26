/*
    Chuchu Rocket PC version
    Copyright (C) 2009  Israël Hallé, isra017@gmail.com
	This file is part of Chuchu Rocket
	http://code.google.com/p/chuchurocket/

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HW_CLOCK_H
#define HW_CLOCK_H

#include <SFML/System.hpp>

class CClock
{
    public:
        CClock();

		//retourne le temps passer depuis la mise en marche
        float getTick();

		//met en pause
        void pause();
		//start le timer
        void play();
		//arrete le timer (remet a 0 et en pause)
        void stop();
		//pause/mise en marche
        void toggle();
		//remet le timer a 0
        void reset();

		//True si l'horloge est en marche
		bool isRunning();

    protected:
    private:
        bool m_isRunning;
        float m_delay;
        float m_stopTick;
        sf::Clock m_clock;
};

#endif // HW_CLOCK_H
