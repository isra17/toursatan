#include "CPlateform.h"

CPlateform::CPlateform(boost::shared_ptr<IModel> model)
	:	IEntity(model), m_isFloor(true), m_isRoof(true)
{

}

//Bloque ou non
IEntity::CollisionType CPlateform::onTouch(boost::shared_ptr<IEntity> other)
{
	CollisionType colType = NOTHING;
	if(m_isFloor && m_isRoof)
		colType = BLOCK;
	if(m_isFloor && other->getCoord().y + other->getDim().y <= getCoord().y)
		colType = BLOCK;
	else if(m_isRoof && other->getCoord().y >= getCoord().y + getDim().y)
		colType = BLOCK;
		
	return colType;
}

//Definit si reagit comme un plancher (les entity ne passe pas au travers si elle vienne d'en haut
void CPlateform::setFloor(bool isFloor)
{
	m_isFloor = isFloor;
}

//Definit si reagit comme un plafond (les entity ne passe pas au travers si elle vienne d'en bas
void CPlateform::setRoof(bool isRoof)
{
	m_isRoof = isRoof;
}

