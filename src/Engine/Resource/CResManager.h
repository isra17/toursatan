#ifndef CRESMANAGER_H
#define CRESMANAGER_H
 
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
 
template< class ResourceKey, class ResourceType >
//!Gestionnaire de ressources
class CResManager {
public:
	typedef boost::shared_ptr<ResourceType> ResourcePtr;
	typedef std::pair< ResourceKey, ResourcePtr > Resource;
    typedef std::map< ResourceKey, ResourcePtr > ResourceMap;
 
 
    ResourcePtr get( const ResourceKey& id ) {
		ResourceMap::iterator resIt = m_resources.find( id );
		//Look if the resource exist
        if( resIt == m_resources.end() ) 
		{
			//load the resource
            ResourcePtr resource = load( id );
			if( resource )
			{
                m_resources.insert( Resource( id, resource ) );
				return resource;
			}

        }
		else
			return resIt->second;
		return ResourcePtr();
    }
 
    void releaseUnusedResources() {
		for(ResourceMap::const_iterator i = m_resources.begin(); i!=m_resource.end();i++)
		{
			if(i->second.unique())
				m_resources.erase(i);
		}
    }

protected:
	virtual ResourcePtr load( const ResourceKey& id ) = 0;

private:
    ResourceMap m_resources;
};
 
#endif // RESOURCEMANAGER_H_INCLUDED