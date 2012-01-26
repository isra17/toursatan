#include "CImageResManager.h"

boost::shared_ptr<sf::Image> CImageResManager::load( const std::string& id )
{
	boost::shared_ptr<sf::Image> newImage(new sf::Image());
	if(!newImage->LoadFromFile(id))
		return CResManager::ResourcePtr();
	return newImage;
}