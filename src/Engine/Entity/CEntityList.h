#ifndef CENTITYLIST_H
#define CENTITYLIST_H

#include "CBaseHandle.h"

#include <boost/shared_ptr.hpp>

#include <map>
#include <set>

//!Handle d'une entity
class IEntity;

//!Liste d'entity (handle)
class CEntityList
{
    public:

        typedef std::map<CBaseHandle, boost::shared_ptr<IEntity>, CHandleCmp>::iterator itEntity;
        typedef std::map<CBaseHandle, boost::shared_ptr<IEntity>, CHandleCmp>::const_iterator constitEntity;

        ~CEntityList();
        itEntity begin();
        itEntity end();

		//!Ajoute un nouvel entité à la liste et retourne son nouveau handle
        CBaseHandle addEntity(boost::shared_ptr<IEntity> entity);
		//!Ajoute une entity au jeu avec un handle precis (remplace l'entity existante si il y en a une deja)
        void addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle);

		//!Retire un entité à la liste (et libère son handle)
		boost::shared_ptr<IEntity> removeEntity(CBaseHandle hHandle);

		//!Retrouve une entity selon son handle
        boost::shared_ptr<IEntity> getEntity(const CBaseHandle& hHandle);

    private:
		//!Retourne le prochain handle libre
        CBaseHandle getFreeHandle();

		//!Map[handle] = entity)
        std::map<CBaseHandle, boost::shared_ptr<IEntity>, CHandleCmp> m_entityList;
		//!Liste des prochain handle disponible
        std::set<CBaseHandle, CHandleCmp> m_nextFreeHandle;
};

#endif
