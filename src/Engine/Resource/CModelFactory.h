#ifndef CMODELFACTORY_H
#define CMODELFACTORY_H

#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <map>

#include "CImageResManager.h"

class IModel;

//!Factory pour la création des modèles
class CModelFactory
{
public:
	typedef std::map<std::string, boost::shared_ptr<IModel> > ModelMap;

	CModelFactory(const boost::property_tree::ptree& ptree, CImageResManager& imageManager);

	boost::shared_ptr<IModel> createModel(std::string name) const;

private:

	boost::shared_ptr<IModel> newModel(const boost::property_tree::ptree::value_type ptPair) const;

	std::map<std::string, boost::shared_ptr<IModel> > m_models;
	CImageResManager& m_imageManager;
};

#endif