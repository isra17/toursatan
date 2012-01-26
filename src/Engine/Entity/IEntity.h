#ifndef IENTITY_H
#define IENTITY_H

#include "CHandle.h"

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <SFML/Graphics.hpp>

class IModel;

///////////////////////////////////////////////////////////
//////////////IMPLEMENTATION MACRO/////////////////////////
///////////////////////////////////////////////////////////


//!Implemente quelque outils pour les entity
#define ENTITY(classname)\
	virtual const std::string className(){return std::string(#classname);}

///////////////////////////////////////////////////////////
///////////////IENTITY CLASS///////////////////////////////
///////////////////////////////////////////////////////////

//!Base des entity dans le jeu
class IEntity : public boost::enable_shared_from_this<IEntity>
{
    public:
		//Implemente la base
        ENTITY(IEntity)

		IEntity(boost::shared_ptr<IModel> model = boost::shared_ptr<IModel>());

        virtual ~IEntity();

		virtual void update(float timeElapsed){}

	private:
		IEntity(const IEntity& ent);
		IEntity& operator=(const IEntity&);
		

    /////////////////////////////////////////////////////////////////
    ////////////////////IENTITYHANDLE'S IMPLEMENTATION///////////////
    /////////////////////////////////////////////////////////////////
    public:
        //!Assigne un handle a l'entity
        void setHandle(const CHandle& hHandle);

		//!Retourne le handle transformé CHandle
		CHandle getHandle() const;

    private:
        //Handle de reference de l'entity
        CHandle m_hHandle;

    /////////////////////////////////////////////////////////////////
    //////////////ICOLLIDEBJECT'S IMPLEMENTATION/////////////////////
    /////////////////////////////////////////////////////////////////
public:
	
	enum CollisionType{
		NOTHING,
		BLOCK,
		KILLENNEMY,
		KILLHERO,
	};

	struct SCollisionInfo{
		SCollisionInfo():validMove(-1.f){}
		boost::shared_ptr<IEntity> otherEntity;
		float validMove;
	};



	//!Reaction face au collision avec une autre enitty
	virtual CollisionType onTouch(boost::shared_ptr<IEntity> other);

	//!Supprime l'entity lorsque en dehors de l'ecran
	virtual void outOfRange();

	//!Définit la coordonne de l'objet
	sf::Vector2f getCoord() const;
	//!Retourne la coordonne de l'objet
	void setCoord(const sf::Vector2f& coord);

	sf::Vector2f getDim();
	void setDim(sf::Vector2f dim);

protected:
	std::vector<IEntity::SCollisionInfo> testHorizontalCollision(float move);
	std::vector<IEntity::SCollisionInfo> testVerticalCollision(float move);

private:
	sf::Vector2f m_coord;
	sf::Vector2f m_dim;


	/////////////////////////////////////////////////////////////////
	/////////////////////IDRAWABLEOBJECT'S IMPLEMENTATION////////////
	/////////////////////////////////////////////////////////////////
public:
	//!Definit l'animation du model (ou sous model...)
	void setModel(std::string modelAnimName);
	//!Retourne le model
	boost::shared_ptr<IModel> getModel() const;
private:
	boost::shared_ptr<IModel> m_model;

};

#endif

