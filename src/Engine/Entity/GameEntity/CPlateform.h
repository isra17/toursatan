#ifndef CPLATEFORM_H
#define CPLATEFORM_H

#include "../IEntity.h"

//!L'entité des plateformes
class CPlateform : public IEntity
{
public :
	ENTITY(CPlateform)

	CPlateform(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

	//!Bloque ou non
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!Definit si reagit comme un plancher (les entity ne passe pas au travers si elle vienne d'en haut
	void setFloor(bool isFloor);
	//!Definit si reagit comme un plafond (les entity ne passe pas au travers si elle vienne d'en bas
	void setRoof(bool isRoof);
private:
	bool m_isRoof;
	bool m_isFloor;
};

#endif

