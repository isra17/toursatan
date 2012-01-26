#include "CBlockModel.h"

#include "../../Misc/CTourException.h"

CBlockModel::CBlockModel(sf::Vector2<unsigned int> cornerTileSize, sf::Vector2<unsigned int> centerTileSize)
{
	m_cornerTileSize = cornerTileSize;
	m_centerTileSize = centerTileSize;
}

void CBlockModel::addBlock(std::string blockName, boost::shared_ptr<sf::Sprite> block)
{	
	if(blockName=="CornerTopLeft")
		m_blockMap[CORNERTOPLEFT]=block;
	else if(blockName=="CornerTopRight")
		m_blockMap[CORNERTOPRIGHT]=block;
	else if(blockName=="CornerBottomLeft")
		m_blockMap[CORNERBOTTOMLEFT]=block;
	else if(blockName=="CornerBottomRight")
		m_blockMap[CORNERBOTTOMRIGHT]=block;
	else if(blockName=="SideLeft")
		m_blockMap[SIDELEFT]=block;
	else if(blockName=="SideRight")
		m_blockMap[SIDERIGHT]=block;
	else if(blockName=="SideTop")
		m_blockMap[SIDETOP]=block;
	else if(blockName=="SideBottom")
		m_blockMap[SIDEBOTTOM]=block;
	else if(blockName=="Center")
		m_blockMap[CENTER]=block;
}

void CBlockModel::setAnim(std::string modelAnimName)
{
	
}

void CBlockModel::setSize(sf::Vector2<unsigned int> size)
{
	if(size.x >= m_cornerTileSize.x * 2 && size.y % m_cornerTileSize.y == 0)
	{
		m_blockSize.x = size.x;
		m_blockSize.y = size.y;
	}
	else
		throw CTourException("Invalid block size");
}

boost::shared_ptr<IModel> CBlockModel::clone() const
{
	boost::shared_ptr<CBlockModel> newModel(new CBlockModel(m_cornerTileSize, m_centerTileSize));
	for(int i=0; i<9; i++)
		newModel->m_blockMap[i] = m_blockMap[i];

	return newModel;
}

void CBlockModel::RenderModel(sf::RenderTarget& target) const
{
	sf::Vector2f tilePosition(0,0);
	unsigned int subRectRight;
	
	for(int i = 0; i <= m_blockSize.y - m_centerTileSize.y; i += m_centerTileSize.y)
	{
		if (i == 0)
		{
			m_blockMap[CORNERTOPLEFT]->SetSubRect(sf::IntRect(0, 0, m_cornerTileSize.x, m_cornerTileSize.y));
			m_blockMap[CORNERTOPLEFT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[CORNERTOPLEFT]);
		}
		else if(i == m_blockSize.y - m_centerTileSize.y)
		{
			m_blockMap[CORNERBOTTOMLEFT]->SetSubRect(sf::IntRect(0, m_centerTileSize.y * 2, m_cornerTileSize.x, m_cornerTileSize.y * 3));
			m_blockMap[CORNERBOTTOMLEFT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[CORNERBOTTOMLEFT]);
		}
		else
		{
			m_blockMap[SIDELEFT]->SetSubRect(sf::IntRect(0, m_centerTileSize.y, m_cornerTileSize.x, m_centerTileSize.y * 2));
			m_blockMap[SIDELEFT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[SIDELEFT]);
		}
	}
	tilePosition.x += m_cornerTileSize.x;

	while(tilePosition.x < m_blockSize.x - m_cornerTileSize.x)
	{
		if(tilePosition.x + m_centerTileSize.x + m_cornerTileSize.x > m_blockSize.x)
			subRectRight = (unsigned int)(m_blockSize.x - tilePosition.x);
		else
			subRectRight = m_centerTileSize.x + m_cornerTileSize.x;

		for(int i = tilePosition.y; i <= m_blockSize.y - m_centerTileSize.y; i += m_centerTileSize.y)
		{
			if (i == 0)
			{
				m_blockMap[SIDETOP]->SetSubRect(sf::IntRect(m_cornerTileSize.x, 0, subRectRight, m_centerTileSize.y));
				m_blockMap[SIDETOP]->SetPosition(tilePosition.x,i);
				target.Draw(*m_blockMap[SIDETOP]);
			}
			else if(i == m_blockSize.y - m_centerTileSize.y)
			{
				m_blockMap[SIDEBOTTOM]->SetSubRect(sf::IntRect(m_cornerTileSize.x, m_centerTileSize.y * 2, subRectRight, m_centerTileSize.y * 3));
				m_blockMap[SIDEBOTTOM]->SetPosition(tilePosition.x,i);
				target.Draw(*m_blockMap[SIDEBOTTOM]);
			}
			else
			{
				m_blockMap[CENTER]->SetSubRect(sf::IntRect(m_cornerTileSize.x, m_centerTileSize.y, subRectRight, m_centerTileSize.y * 3));
				m_blockMap[CENTER]->SetPosition(tilePosition.x,i);
				target.Draw(*m_blockMap[CENTER]);
			}
		}
		tilePosition.x += subRectRight - m_cornerTileSize.x;
	}

	for(int i = tilePosition.y; i <= m_blockSize.y - m_centerTileSize.y; i += m_centerTileSize.y)
	{
		if (i == 0)
		{
			m_blockMap[CORNERTOPRIGHT]->SetSubRect(sf::IntRect(m_cornerTileSize.x + m_centerTileSize.x, 0, (m_cornerTileSize.x * 2) + m_centerTileSize.x, m_cornerTileSize.y));
			m_blockMap[CORNERTOPRIGHT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[CORNERTOPRIGHT]);
		}
		else if(i == m_blockSize.y - m_centerTileSize.y)
		{
			m_blockMap[CORNERBOTTOMRIGHT]->SetSubRect(sf::IntRect(m_cornerTileSize.x + m_centerTileSize.x, m_cornerTileSize.y * 2, (m_cornerTileSize.x * 2) + m_centerTileSize.x, m_cornerTileSize.y * 3));
			m_blockMap[CORNERBOTTOMRIGHT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[CORNERBOTTOMRIGHT]);
		}
		else
		{
			m_blockMap[SIDERIGHT]->SetSubRect(sf::IntRect(m_cornerTileSize.x + m_centerTileSize.x, m_cornerTileSize.y, (m_cornerTileSize.x * 2) + m_centerTileSize.x, m_centerTileSize.y * 2));
			m_blockMap[SIDERIGHT]->SetPosition(tilePosition.x,i);
			target.Draw(*m_blockMap[SIDERIGHT]);
		}
	}
	tilePosition.x += m_cornerTileSize.x;
}