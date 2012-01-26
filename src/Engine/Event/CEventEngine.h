#ifndef CEVENTENGINE_H
#define CEVENTENGINE_H

#include <boost/weak_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "../CGameEngine.h"
#include "CEvent.h"
#include <queue>

//!Moteur qui gère les évènements du jeu
class CEventEngine
{
    public:
		typedef boost::shared_ptr<CEvent> EventPtr;

		CEventEngine();

		//!Cree un nouvelle event
		virtual void newEvent(EventPtr event);

		//!Procede un evenement de jeux (a utiliser pour lancer un evenement en temps normal)
		virtual void handleEvent(EventPtr event);

		//!procede les evenement dans la liste
        virtual void onFrame(float m_lastFrame);

		//!Thread safe (a utiliser lorsque l'appelant est dans un autre thread seulement
		void pushEvent(EventPtr event);

    private:
		//Queue d'evenement a traiter pour le thread-safe
		std::queue<EventPtr> m_events;

		//syncro de la queue d'event
		//pour quelque raison que ce soit, si le mutex n'est pas static une erreur de compilation apparait sur certaine machine
		static boost::mutex m_evMutex;
};

#endif // CEVENTENGINE_H
