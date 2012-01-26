#ifndef IMODEL_H
#define IMODEL_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

//!Interface d'un objet qui peut faire des collision avec d'autre objet
class IModel : public sf::Drawable
{
public:
	IModel() : m_isActive(true){};

	//Definit l'animation du model (ou sous model...)
	virtual void setAnim(std::string modelAnimName)=0;

	//Definit la taille du modèle(pour les blocs)
	virtual void setSize(sf::Vector2<unsigned int> size){};

	//copie le modele
	virtual boost::shared_ptr<IModel> clone() const=0;	

	//Rend le drawable
	void Render(sf::RenderTarget& target) const 
	{
		if(m_isActive)
			RenderModel(target);
	}; 

	virtual void RenderModel(sf::RenderTarget& target) const = 0; 

	//(des)Active le model
	virtual void setActive(bool isActive) {m_isActive = isActive;};

private:
	bool m_isActive;
};

#endif