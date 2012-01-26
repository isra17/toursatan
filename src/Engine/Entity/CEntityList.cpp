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

#include "CEntityList.h"
#include "IEntity.h"

#include "../Log/CLog.h"


CEntityList::~CEntityList()
{
};

CEntityList::itEntity CEntityList::begin()
{
    return m_entityList.begin();
}

CEntityList::itEntity CEntityList::end()
{
    return m_entityList.end();
}

CBaseHandle CEntityList::addEntity(boost::shared_ptr<IEntity> entity)
{
	//Log la suppression
	CLog::debug("Nouvelle entity [" + entity->className() + "]");

	//Requete d'un handle libre
    CBaseHandle hHandle = getFreeHandle();
    assert(m_entityList.find(hHandle)==m_entityList.end());

	//ajoute le handle a la liste et initialise l'entity
    m_entityList[hHandle]=entity;
    entity->setHandle(hHandle);
    return hHandle;
}

void CEntityList::addEntity(boost::shared_ptr<IEntity> entity, const CBaseHandle& handle)
{
	//Log la suppression
	CLog::debug("Nouvelle entity [" + entity->className() + "]");

	//ajoute le handle a la liste et initialise l'entity
    m_entityList[handle]=entity;
    entity->setHandle(handle);
}

boost::shared_ptr<IEntity> CEntityList::removeEntity(CBaseHandle hHandle)
{
	boost::shared_ptr<IEntity> entityDeleted;
	//Retrouve le handle dans la liste
    itEntity deleted = m_entityList.find(hHandle);
	//Verifie qu'il est valide
    if(deleted != m_entityList.end() && deleted->first == hHandle)
    {
		entityDeleted = deleted->second;

		//Log la suppression
		CLog::debug("Supression de l'entity [" + entityDeleted->className() + "]");

		//Rend invalide le handle de l'entity
        deleted->second->setHandle(CBaseHandle());
		//Met le handle dans la liste des handle libre
        m_nextFreeHandle.insert(deleted->first);
		//Retire le handle de la liste
        m_entityList.erase(deleted);
    }

	return entityDeleted;
}

//Retourne l'entity associe a l'handle
boost::shared_ptr<IEntity> CEntityList::getEntity(const CBaseHandle& hHandle)
{
    boost::shared_ptr<IEntity> pEntity;
	//retrouve le handle
    constitEntity entity = m_entityList.find(hHandle);
	//s'assure qu'il est valide
    if(entity != m_entityList.end())
        if(entity->second && hHandle==entity->second->getHandle())
            pEntity=entity->second;
    return pEntity;
}

CBaseHandle CEntityList::getFreeHandle()
{
	CBaseHandle freeHandle;
	//si on a des handle dans la liste des handle recyclable on le retourne
    if(m_nextFreeHandle.size() > 0)
    {
        CBaseHandle handle = *m_nextFreeHandle.begin();
        CBaseHandle newHandle(handle.getIndex(), handle.getSerial()+1);
        m_nextFreeHandle.erase(handle);
        freeHandle = newHandle;
    }
	//Sinon crer un nouvelle handle
	else if(m_entityList.size() == 0)
		freeHandle = CBaseHandle(1,0);
	else
		freeHandle = CBaseHandle(m_entityList.rbegin()->first.getIndex()+1, 0);
    
	return freeHandle;
}

