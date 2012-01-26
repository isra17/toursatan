#include "CLevelLoader.h"

#include "../Misc/BasicType.h"
#include "../Resource/CResourceEngine.h"
#include "../Log/CLog.h"
#include "../Graphics/Model/CRectModel.h"

#include "CLevel.h"

#include "../Entity/GameEntity/CHero.h"
#include "../Entity/GameEntity/CDemon.h"
#include "../Entity/GameEntity/CPofin.h"
#include "../Entity/GameEntity/CDebris.h"
#include "../Entity/GameEntity/CPlateform.h"
#include "../Entity/GameEntity/CCoin.h"

using namespace boost::property_tree;

void CLevelLoader::load(ptree levelRoot, boost::shared_ptr<CLevel> level, boost::shared_ptr<CResourceEngine> resEngine)
{
	//Info du level
	ptree ptLevelInfo = levelRoot.get_child("LevelInfo");
	level->setEndLevel(-ptLevelInfo.get<float>("endLevel"));

	//fond du level
	boost::shared_ptr<sf::Image> backgroundImg(resEngine->getImageResManager().get(ptLevelInfo.get<std::string>("background")));
	boost::shared_ptr<sf::Sprite> backgroundSprite(new sf::Sprite(*backgroundImg));
	level->setBackgroundSprite(backgroundSprite);

	boost::shared_ptr<sf::Image> borderImg(resEngine->getImageResManager().get(ptLevelInfo.get<std::string>("borderBackground")));
	boost::shared_ptr<sf::Sprite> borderSprite(new sf::Sprite(*borderImg));
	level->setBorderSprite(borderSprite);

	//Ajoute les spawn location
	foreach(ptree::value_type &ptSpawn, levelRoot.get_child("PlayerSpawn"))
	{
		sf::Vector2f coord;
		coord.x = ptSpawn.second.get<float>("x");
		coord.y = -ptSpawn.second.get<float>("y");

		level->addSpawnLocation(coord);
	}

	//Ajoute les entities
	foreach(ptree::value_type &ptEntity, levelRoot.get_child("EntityList"))
	{
		boost::shared_ptr<IEntity> newEnt;
		std::string name = ptEntity.first;
		if(name == "Block")
			newEnt = createBlock(ptEntity.second);
		else if(name == "Demon")
			newEnt = createDemon(ptEntity.second);
		else if(name == "Pofin")
			newEnt = createPofin(ptEntity.second);
		else if(name == "Debris")
			newEnt = createDebris(ptEntity.second);
		else if(name == "Plateforme")
			newEnt = createPlateforme(ptEntity.second);
		else if(name == "Coin")
			newEnt = createCoin(ptEntity.second);


		level->addEntity(newEnt);
	}
}

//Creer un nouveau block
boost::shared_ptr<IEntity> CLevelLoader::createBlock(ptree ptBlock)
{
	float width = ptBlock.get<float>("w", 100.f);
	float height = ptBlock.get<float>("h", 100.f);
	boost::shared_ptr<IModel> model(new CRectModel(sf::Color::Yellow,sf::Vector2f(width,height)));
	boost::shared_ptr<IEntity> entBlock(new IEntity(model));

	entBlock->setDim(sf::Vector2f(width,height));

	sf::Vector2f coord;
	coord.x = ptBlock.get<float>("x");
	coord.y = -ptBlock.get<float>("y");
	entBlock->setCoord(coord);

	return entBlock;
}

//Crer un demon
boost::shared_ptr<IEntity> CLevelLoader::createDemon(boost::property_tree::ptree ptDemon)
{
	float speed = ptDemon.get<float>("fireball_speed");
	float interval = ptDemon.get<float>("fireball_interval", 2.f);
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("Demon"));
	boost::shared_ptr<IEntity> entDemon(new CDemon(speed,interval,model));

	entDemon->setDim(sf::Vector2f(50,90));

	sf::Vector2f coord;
	coord.x = ptDemon.get<float>("x");
	coord.y = -ptDemon.get<float>("y");
	entDemon->setCoord(coord);

	return entDemon;
}

//Cree un pofin
boost::shared_ptr<IEntity> CLevelLoader::createPofin(boost::property_tree::ptree ptPofin)
{
	float speed = ptPofin.get<float>("speed", 200.f);
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("Pofin"));
	boost::shared_ptr<IEntity> entPofin(new CPofin(speed, model));

	entPofin->setDim(sf::Vector2f(50,50));

	sf::Vector2f coord;
	coord.x = ptPofin.get<float>("x");
	coord.y = -ptPofin.get<float>("y");
	entPofin->setCoord(coord);


	return entPofin;
}

//Crer un debris
boost::shared_ptr<IEntity> CLevelLoader::createDebris(boost::property_tree::ptree ptDebris)
{
	float width = ptDebris.get<float>("w", 75.f);
	float height = ptDebris.get<float>("h", 100.f);
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("Debris"));
	boost::shared_ptr<IEntity> entDebris(new CDebris(model));

	entDebris->setDim(sf::Vector2f(width,height));

	sf::Vector2f coord;
	coord.x = ptDebris.get<float>("x");
	coord.y = -ptDebris.get<float>("y");
	entDebris->setCoord(coord);

	return entDebris;
}

boost::shared_ptr<IEntity> CLevelLoader::createPlateforme(boost::property_tree::ptree ptPlateforme)
{
	float width = ptPlateforme.get<float>("w", 100.f);
	float height = ptPlateforme.get<float>("h", 100.f);
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("Block"));
	//boost::shared_ptr<IModel> model(new CRectModel(sf::Color::Red, sf::Vector2f(width,height)));
	model->setSize(*(new sf::Vector2<unsigned int>(static_cast<unsigned int>(width),static_cast<unsigned int>(height))));
	boost::shared_ptr<CPlateform> entPlateform(new CPlateform(model));

	entPlateform->setDim(sf::Vector2f(width,height));

	sf::Vector2f coord;
	coord.x = ptPlateforme.get<float>("x");
	coord.y = -ptPlateforme.get<float>("y");
	entPlateform->setCoord(coord);

	bool isFloor = ptPlateforme.get<bool>("isFloor", true);
	bool isRoof = ptPlateforme.get<bool>("isRoof", true);

	entPlateform->setFloor(isFloor);
	entPlateform->setRoof(isRoof);

	return entPlateform;
}

//Creer un nouveau Coin
boost::shared_ptr<IEntity> CLevelLoader::createCoin(ptree ptCoin)
{
	float width = ptCoin.get<float>("w", 28.f);
	float height = ptCoin.get<float>("h", 32.f);
	boost::shared_ptr<IModel> model(CGameEngine::instance()->getResEngine()->getModel("Coin"));
	boost::shared_ptr<CCoin> entCoin(new CCoin(model));

	entCoin->setDim(sf::Vector2f(width,height));

	sf::Vector2f coord;
	coord.x = ptCoin.get<float>("x");
	coord.y = -ptCoin.get<float>("y");
	entCoin->setCoord(coord);

	return entCoin;
}

