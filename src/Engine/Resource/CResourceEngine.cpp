#include "CResourceEngine.h"

#include <boost/property_tree/info_parser.hpp>
#include "CModelFactory.h"

#include <iostream>

CResourceEngine::CResourceEngine()
{
	boost::property_tree::ptree pt;
	try{
		read_info("data/NewModels.info",pt);
		m_modelFactory = boost::shared_ptr<CModelFactory>(new CModelFactory(pt,m_imageManager));
	}
	catch(boost::property_tree::ptree_error ptError)
	{
		
	}
	catch(std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}	
}

boost::shared_ptr<IModel> CResourceEngine::getModel(std::string name) const
{
	return m_modelFactory->createModel(name);
}

CImageResManager& CResourceEngine::getImageResManager()
{
	return m_imageManager;
}

