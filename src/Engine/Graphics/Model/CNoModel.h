#ifndef CNOMODEL_H
#define CNOMODEL_H

#include <SFML/Graphics.hpp>
#include "IModel.h"

//!Model qui ne rend rien
class CNoModel : public IModel
{
public:
	//Pas de sous-model pour le rectangle...
	virtual void setAnim(std::string modelAnimName){}

	virtual boost::shared_ptr<IModel> clone()  const
	{
		boost::shared_ptr<IModel> newModel(new CNoModel());
		return newModel;
	}

	//Ne rend rien
	virtual void RenderModel(sf::RenderTarget&) const {} 
};

#endif