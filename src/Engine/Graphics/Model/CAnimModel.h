#ifndef CANIMMODEL_H
#define CANIMMODEL_H

#include <SFML/Graphics.hpp>
#include "../CImgAnim.h"
#include "IModel.h"

//!Model qui ne rend rien
class CAnimModel : public IModel
{
public:
	CAnimModel(CImgAnim anim);
	void setModelRow(std::string modelName, int row);

	virtual void setAnim(std::string modelAnimName);

	virtual boost::shared_ptr<IModel> clone() const;

	virtual void RenderModel(sf::RenderTarget& target) const;
private:
	CImgAnim m_anim;
	std::map<std::string, int> m_animMap;
};

#endif