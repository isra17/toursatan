#ifndef CSATANMODEL_H
#define CSATANMODEL_H

#include "IModel.h"

//!Interface d'un objet qui peut faire des collision avec d'autre objet
class CSatanModel : public IModel
{
public:
	CSatanModel(boost::shared_ptr<IModel> heroModel, boost::shared_ptr<IModel> satanModel);

	//Definit l'animation du model (ou sous model...)
	virtual void setAnim(std::string modelAnimName);

	//copie le modele
	virtual boost::shared_ptr<IModel> clone() const;	

	//Rend le drawable
	virtual void RenderModel(sf::RenderTarget& target) const; 

	//Active le hero
	void setActiveHero(bool isActive);
private:
	boost::shared_ptr<IModel> m_heroModel;
	boost::shared_ptr<IModel> m_satanModel;
};

#endif