#include "IEntity.h"
#include <iostream>

#include "../Graphics/Model/CNoModel.h"
#include "../Log/CLog.h"
#include "../Util.h"

using namespace std;

IEntity::IEntity(boost::shared_ptr<IModel> model)
{
	if(model)
		m_model=model;
	else
		m_model = boost::shared_ptr<IModel>(new CNoModel);
}


IEntity::~IEntity()
{
}

/////////////////////////////////////////////////////////////////
////////////////////IENTITYHANDLE'S IMPLEMENTATION///////////////
/////////////////////////////////////////////////////////////////

void IEntity::setHandle(const CHandle& hHandle){
    m_hHandle = hHandle;
}
CHandle IEntity::getHandle() const{
    return m_hHandle;
}


/////////////////////////////////////////////////////////////////
//////////////IPHYSICOBJECT'S IMPLEMENTATION/////////////////////
/////////////////////////////////////////////////////////////////

IEntity::CollisionType IEntity::onTouch(boost::shared_ptr<IEntity> other)
{
	//cout << "IEntity(" << className() << "){"<<getHandle()<<"}::onTouch(" << hOther << ");" << endl;
	return BLOCK;
}

std::vector<IEntity::SCollisionInfo> IEntity::testHorizontalCollision(float move)
{
	boost::shared_ptr<CEntityList> entityList = CGameEngine::instance()->getEntityList();
	std::vector<IEntity::SCollisionInfo> collisionInfoVec;

	for(CEntityList::constitEntity i=entityList->begin();i!=entityList->end();i++)
	{
		//S'assure que ce n'est pas cet entity
		if(getHandle() != i->second->getHandle())
		{
			//propriete de lautre entity
			sf::Vector2f oCoord = i->second->getCoord();
			sf::Vector2f oDim = i->second->getDim();

			//Retangle des 2 entity
			sf::FloatRect oRect(oCoord.x,oCoord.y,oCoord.x+oDim.x,oCoord.y+oDim.y);
			sf::FloatRect thisRect(m_coord.x,m_coord.y,m_coord.x+m_dim.x,m_coord.y+m_dim.y);
			thisRect.Offset(move,0);

			//Test la collision
			if(thisRect.Intersects(oRect))
			{
				float validMove=0.f;
				if(move > 0)
					validMove = oRect.Left - (m_coord.x+m_dim.x);
				else if(move < 0)
					validMove = oRect.Right - m_coord.x;
				if(move != 0.f)
				{
					IEntity::SCollisionInfo collisionInfo;
					collisionInfo.validMove = validMove;
					collisionInfo.otherEntity = i->second;

					collisionInfoVec.push_back(collisionInfo);
				}
			}
		}
	}
	return collisionInfoVec;
}

std::vector<IEntity::SCollisionInfo> IEntity::testVerticalCollision(float move)
{
	boost::shared_ptr<CEntityList> entityList = CGameEngine::instance()->getEntityList();
	std::vector<IEntity::SCollisionInfo> collisionInfoVec;

	for(CEntityList::constitEntity i=entityList->begin();i!=entityList->end();i++)
	{
		//S'assure que ce n'est pas cet entity
		if(getHandle() != i->second->getHandle())
		{
			//propriete de lautre entity
			sf::Vector2f oCoord = i->second->getCoord();
			sf::Vector2f oDim = i->second->getDim();

			//Retangle des 2 entity
			sf::FloatRect oRect(oCoord.x,oCoord.y,oCoord.x+oDim.x,oCoord.y+oDim.y);
			sf::FloatRect thisRect(m_coord.x,m_coord.y,m_coord.x+m_dim.x,m_coord.y+m_dim.y);
			thisRect.Offset(0,move);

			//Test la collision
			if(thisRect.Intersects(oRect))
			{
				float validMove=0.f;
				if(move > 0)
					validMove = oRect.Top - (m_coord.y+m_dim.y);
				else if(move < 0)
					validMove = oRect.Bottom - m_coord.y;
				if(move != 0.f)
				{
					IEntity::SCollisionInfo collisionInfo;
					collisionInfo.validMove = validMove;
					collisionInfo.otherEntity = i->second;

					collisionInfoVec.push_back(collisionInfo);
				}
			}
		}
	}
	return collisionInfoVec;
}

//set/get de la coordonne de l'objet
sf::Vector2f IEntity::getCoord() const
{
	return m_coord;
}

void IEntity::setCoord(const sf::Vector2f& coord)
{
	m_coord = coord;
}

sf::Vector2f IEntity::getDim()
{
	return m_dim;
}

void IEntity::setDim(sf::Vector2f dim)
{
	m_dim = dim;
}


/////////////////////////////////////////////////////////////////
/////////////////////IDRAWABLEOBJECT'S IMPLEMENTATION////////////
/////////////////////////////////////////////////////////////////

//Definit l'animation du model (ou sous model...)
void IEntity::setModel(std::string modelAnimName)
{
	m_model->setAnim(modelAnimName);
}

boost::shared_ptr<IModel> IEntity::getModel() const
{
	return m_model;
}

void IEntity::outOfRange()
{
	CGameEngine::instance()->deleteEntity(getHandle(),true);
}

