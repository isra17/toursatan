#include "CMapModel.h"

CMapModel::CMapModel()
{
}

void CMapModel::addAnim(std::string animName, boost::shared_ptr<sf::Drawable> anim)
{
	m_animMap[animName] = anim;
}

void CMapModel::setAnim(std::string modelAnimName)
{
	std::map<std::string, boost::shared_ptr<sf::Drawable> >::const_iterator animIt = m_animMap.find(modelAnimName);
	if(animIt!=m_animMap.end())
		m_currentAnim = modelAnimName;
}

boost::shared_ptr<IModel> CMapModel::clone() const
{
	boost::shared_ptr<CMapModel> newModel(new CMapModel());
	newModel->m_animMap = m_animMap;
	return newModel;
}

void CMapModel::RenderModel(sf::RenderTarget& target) const
{
	std::map<std::string, boost::shared_ptr<sf::Drawable> >::const_iterator animIt = m_animMap.find(m_currentAnim);
	if(animIt!=m_animMap.end())
		target.Draw(*(animIt->second));
}
