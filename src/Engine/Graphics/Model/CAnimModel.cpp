#include "CAnimModel.h"

CAnimModel::CAnimModel(CImgAnim anim) : m_anim(anim)
{

}

void CAnimModel::setModelRow(std::string modelName, int row)
{
	m_animMap[modelName] = row;
}

void CAnimModel::setAnim(std::string modelAnimName)
{
	std::map<std::string, int>::const_iterator rowIt = m_animMap.find(modelAnimName);
	if(rowIt!=m_animMap.end())
		m_anim.setAnimRow(rowIt->second);
}

boost::shared_ptr<IModel> CAnimModel::clone() const
{
	boost::shared_ptr<CAnimModel> newModel(new CAnimModel(m_anim));
	newModel->m_animMap = m_animMap;
	return newModel;
}

void CAnimModel::RenderModel(sf::RenderTarget& target) const
{
	target.Draw(m_anim);
}

