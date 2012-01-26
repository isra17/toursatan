#ifndef CSPRITEMODEL_H
#define CSPRITEMODEL_H

#include <SFML/Graphics.hpp>

#include "IModel.h"

//!Model qui affiche une image non animé
class CSpriteModel : public IModel
{
public:
	CSpriteModel(sf::Sprite sprite) : m_sprite(sprite)
	{	
		m_sprite.SetPosition(m_sprite.GetSize().x/2,m_sprite.GetSize().y/2);
		m_sprite.SetCenter(m_sprite.GetSize().x/2,m_sprite.GetSize().y/2);
	}

	virtual boost::shared_ptr<IModel> clone() const
	{
		boost::shared_ptr<IModel> newModel(new CSpriteModel(*this));
		return newModel;
	}

	virtual void setAnim(std::string modelName)
	{
	}

	virtual void RenderModel(sf::RenderTarget& target) const 
	{
		target.Draw(m_sprite);
	}

private:
	sf::Sprite m_sprite;
};

#endif