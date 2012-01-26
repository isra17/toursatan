#ifndef CRECTMODEL_H
#define CRECTMODEL_H

#include <SFML/Graphics.hpp>
#include "IModel.h"

//!Model qui affiche un rectangle, utile pour debugger
class CRectModel : public IModel
{
public:
	//Pour un rect on a pas 10000 model, juste des rectangle...
	CRectModel(const sf::Color& color, sf::Vector2f size) : m_rect(sf::Shape::Rectangle(sf::Vector2f(0.f,0.f),size,color))
	{}

	virtual boost::shared_ptr<IModel> clone() const
	{
		boost::shared_ptr<IModel> newModel(new CRectModel(*this));
		return newModel;
	}

	//Pas de sous-model pour le rectangle...
	virtual void setAnim(std::string modelAnimName){}

	//Rend le rectangle
	virtual void RenderModel(sf::RenderTarget& target) const 
	{
		target.Draw(m_rect);
	} 

private:
	sf::Shape m_rect;
};

#endif