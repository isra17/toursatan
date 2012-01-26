#ifndef EVENTID_H
#define EVENTID_H

//!Liste des ID des evenement de jeu
enum{
	EVENT_MSG=0,

	//!Bouge un joueur
	EVENT_HEROMOVE=100,
	//!Fait sauter un joueur
	EVENT_HEROJUMP=101,
	//!Arrete le saut d'un joueur
	EVENT_HEROSTOPJUMP=102,
	//!Synchronise un hero
	EVENT_HEROSYNC=103,
	//!Ajoute des points a un joueur
	EVENT_HEROADDSCORE=104,

	//!Debute une session de jeu
	EVENT_NETWORKHELLO=1000,
	//!Synchronis les infos de joueurs
	EVENT_NETWORKSYNCPLAYERDATA=1001,
	//!Debute une partie
	EVENT_NETWORKSTARTGAME=1002,
	//!Client pret
	EVENT_NETWORKCLIENTSTATE=1003
};

#endif