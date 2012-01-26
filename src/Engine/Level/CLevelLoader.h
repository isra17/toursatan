#ifndef CLEVELLOADER_H
#define CLEVELLOADER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/shared_ptr.hpp>

#include <vector>

#include "../CPlayer.h"

class CLevel;
class CResourceEngine;
class IEntity;

//!Gère la création du niveau
class CLevelLoader
{
public:
	static void load(boost::property_tree::ptree levelRoot, boost::shared_ptr<CLevel> level, boost::shared_ptr<CResourceEngine> resEngine);

private:
	static boost::shared_ptr<IEntity> createBlock(boost::property_tree::ptree ptBlock);
	static boost::shared_ptr<IEntity> createDemon(boost::property_tree::ptree ptDemon);
	static boost::shared_ptr<IEntity> createPofin(boost::property_tree::ptree ptPofin);
	static boost::shared_ptr<IEntity> createDebris(boost::property_tree::ptree ptDebris);
	static boost::shared_ptr<IEntity> createPlateforme(boost::property_tree::ptree ptPlateforme);
	static boost::shared_ptr<IEntity> createCoin(boost::property_tree::ptree ptDebris);
};

#endif

