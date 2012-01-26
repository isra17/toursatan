#ifndef CMAPMODEL_H
#define CMAPMODEL_H

#include <SFML/Graphics.hpp>
#include "../CImgAnim.h"
#include "IModel.h"

//!Model qui ne rend rien
class CMapModel : public IModel
{
public:
	CMapModel();

	void addAnim(std::string modelName,boost::shared_ptr<sf::Drawable> anim);
	
	virtual void setAnim(std::string modelAnimName);

	virtual boost::shared_ptr<IModel> clone() const;

	virtual void RenderModel(sf::RenderTarget& target) const;


private:
	std::string m_currentAnim;
	std::map<std::string,boost::shared_ptr<sf::Drawable> > m_animMap;
};

#endif