#ifndef CBLOCKMODEL_H
#define CBLOCKMODEL_H

#include <SFML/Graphics.hpp>
#include "../CImgAnim.h"
#include "IModel.h"
#include "CSpriteModel.h"

//!Model qui ne rend rien
class CBlockModel : public IModel
{
public:
	enum
	{
		CORNERTOPLEFT=0,
		CORNERBOTTOMLEFT=1,
		SIDELEFT=2,
		CORNERTOPRIGHT=3,
		CORNERBOTTOMRIGHT=4,
		SIDERIGHT=5,
		SIDETOP=6,
		SIDEBOTTOM=7,
		CENTER=8
	};


	CBlockModel(sf::Vector2<unsigned int> cornerTileSize, sf::Vector2<unsigned int> centerTileSize);

	void addBlock(std::string blockName,boost::shared_ptr<sf::Sprite> block);
	
	virtual void setAnim(std::string modelAnimName);
	
	virtual void setSize(sf::Vector2<unsigned int> size);
	
	virtual boost::shared_ptr<IModel> clone() const;

	virtual void RenderModel(sf::RenderTarget& target) const;


private:
	boost::shared_ptr<sf::Sprite> m_blockMap[9];
	sf::Vector2<unsigned int> m_cornerTileSize;
	sf::Vector2<unsigned int> m_centerTileSize;
	sf::Vector2<unsigned int> m_blockSize;
};

#endif