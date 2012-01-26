#include "CModelFactory.h"
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <map>

#include "../Graphics/Model/CBlockModel.h"
#include "../Graphics/Model/CMapModel.h"
#include "../Graphics/Model/CSpriteModel.h"

#include "../Misc/CTourException.h"


using boost::property_tree::ptree;

CModelFactory::CModelFactory(const ptree& pt, CImageResManager& imageManager)
: m_imageManager(imageManager)
{
	//Itere dans tout les modele
	BOOST_FOREACH(const ptree::value_type &v, pt.get_child(""))
	{
		//Verifie que le modele n'existe pas deja
		if(m_models.find(v.first) != m_models.end())
		{
			throw CTourException("Trying to register existing model");
		}

		m_models[v.first] = newModel(v);
	}

}

boost::shared_ptr<IModel> CModelFactory::newModel(const ptree::value_type ptPair) const
{
	const ptree modelTree = ptPair.second;
	const std::string imgSrcPath = modelTree.get<std::string>("ImgSrc");
	const std::string modelType = modelTree.get<std::string>("ModelType");
	const boost::shared_ptr<sf::Image> img = m_imageManager.get(imgSrcPath);

	if(modelType=="Anim")
	{
		const ptree frameTree = modelTree.get_child("Frames");
		const unsigned int nbrRow = modelTree.get<unsigned int>("NbrRow");
		const unsigned int maxLine = modelTree.get<unsigned int>("MaxLine");

		boost::shared_ptr<CMapModel> mapModel(new CMapModel());

		BOOST_FOREACH(const ptree::value_type &frame, frameTree.get_child(""))
		{
			ptree ptFrame = frame.second;		

			//Lit les info du frame
			std::string type = ptFrame.get<std::string>("Type");

			sf::Vector2<unsigned int> offset(0,0);
			const ptree offsetTree = ptFrame.get_child("Offset");
			offset.x = offsetTree.get<unsigned int>("x");
			offset.y = offsetTree.get<unsigned int>("y");

			if(type=="Anim")
			{
				//Charge le model			
				unsigned int nbrFrame = ptFrame.get<unsigned int>("NbrFrame");
				float timeDelay = ptFrame.get<float>("TimeDelay", 1.0);
				boost::shared_ptr<CImgAnim> anim(new CImgAnim(*img,nbrFrame,nbrRow,maxLine));
				anim->setDelay(timeDelay);
				anim->setOffset(offset.x,offset.y);

				//Set les frames de l'animation
				mapModel->addAnim(frame.first, anim);
			}
			else if(type=="Sprite")
			{
				sf::Vector2<unsigned int> size(0,0);
				//Lit les info du frame
				const ptree sizeTree = ptFrame.get_child("Size");
				size.x = sizeTree.get<unsigned int>("x");
				size.y = sizeTree.get<unsigned int>("y");
				sf::Sprite sprite(*img);
				sprite.SetSubRect(sf::IntRect(offset.x, offset.y, offset.x+size.x, offset.y+size.y));

				mapModel->addAnim(frame.first, boost::shared_ptr<CSpriteModel>(new CSpriteModel(sprite)));
			}
		else
			throw CTourException("Unknown animation type ("+type+")");
		}	
		return mapModel;
	}

	else if(modelType=="Sprite")
	{
		sf::Sprite sprite(*img);
		sf::Vector2<unsigned int> offset(0,0);
		const ptree offsetTree = modelTree.get_child("Offset");
		offset.x = offsetTree.get<unsigned int>("x");
		offset.y = offsetTree.get<unsigned int>("y");
		sprite.SetSubRect(sf::IntRect(offset.x, offset.y, img->GetWidth(), img->GetHeight()));

		return boost::shared_ptr<CSpriteModel>(new CSpriteModel(sprite));
	}
	else if(modelType=="Block")
	{	
		const ptree frameTree = modelTree.get_child("Frames");
		const ptree cornerSizeTree = modelTree.get_child("CornerSize");
		sf::Vector2<unsigned int> cornerSize(0,0);
		cornerSize.x = cornerSizeTree.get<unsigned int>("x");
		cornerSize.y = cornerSizeTree.get<unsigned int>("y");
		
		const ptree centerSizeTree = modelTree.get_child("CenterSize");
		sf::Vector2<unsigned int> centerSize(0,0);
		centerSize.x = centerSizeTree.get<unsigned int>("x");
		centerSize.y = centerSizeTree.get<unsigned int>("y");

		boost::shared_ptr<CBlockModel> blockModel(new CBlockModel(cornerSize, centerSize));
		BOOST_FOREACH(const ptree::value_type &frame, frameTree.get_child(""))
		{
			ptree ptFrame = frame.second;

			//Lit les info du frame
			boost::shared_ptr<sf::Image> img = m_imageManager.get(imgSrcPath);
			sf::Vector2<unsigned int> offset(0,0);
			const ptree offsetTree = ptFrame.get_child("Offset");
			offset.x = offsetTree.get<unsigned int>("x");
			offset.y = offsetTree.get<unsigned int>("y");

			boost::shared_ptr<sf::Sprite> sprite(new sf::Sprite(*img));

			if(frame.first=="SideTop" || frame.first=="Center" || frame.first=="SideBottom")
				sprite->SetSubRect(sf::IntRect(offset.x,offset.y,offset.x+centerSize.x,offset.y+centerSize.y));
			else
				sprite->SetSubRect(sf::IntRect(offset.x,offset.y,offset.x+cornerSize.x,offset.y+cornerSize.y));

			blockModel->addBlock(frame.first, sprite);
		}
		return blockModel;
	}
	else
		throw CTourException("Unknown model type ("+modelType+")");

}

boost::shared_ptr<IModel> CModelFactory::createModel(std::string name) const
{
	ModelMap::const_iterator modelIt = m_models.find(name);
	if(modelIt != m_models.end())
		return modelIt->second->clone();
	return boost::shared_ptr<IModel>();
}