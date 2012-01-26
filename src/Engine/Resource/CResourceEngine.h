#ifndef CRESOURCEENGINE_H
#define CRESOURCEENGINE_H

#include <boost/shared_ptr.hpp>
#include <string>

#include "CImageResManager.h"

class CModelFactory;
class IModel;

//!Moteur de ressources
class CResourceEngine
{
public:
	CResourceEngine();
	boost::shared_ptr<IModel> getModel(std::string name) const;
	CImageResManager& getImageResManager();

private:
	CImageResManager m_imageManager;
	boost::shared_ptr<CModelFactory> m_modelFactory;
};

#endif

