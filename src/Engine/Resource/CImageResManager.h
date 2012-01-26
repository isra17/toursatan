#ifndef CIMAGERESMANAGER_H
#define CIMAGERESMANAGER_H

#include <boost/shared_ptr.hpp>
#include <string>
#include <SFML/Graphics.hpp>

#include "CResManager.h"

//!Gestionnaire d'images
class CImageResManager : public CResManager<std::string, sf::Image>
{
protected:
	virtual CResManager::ResourcePtr load( const std::string& strId );
};

#endif