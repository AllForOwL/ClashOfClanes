#ifndef __RESOURCES_FACTORY_H__
#define __RESOURCES_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class MapLayer;


class ResourcesFactory : public Factory
{
public:

	enum StateFactoryResources
	{
		START_GOLD,
		START_OIL,
		WORKING_GOLD,
		WORKING_OIL,
		LISTEN,
		NOTHING
	};

	ResourcesFactory();
	ResourcesFactory(Point i_positionVisible, MapLayer& i_mapLayer, std::string i_filename);
	ResourcesFactory(ResourcesFactory& i_ResourcesFactory);

	~ResourcesFactory();

	void SetTypeResources(int i_type);


	virtual void Update(ManagerComponent& i_manager);

private:
	StateFactoryResources	m_stateResources;
	int						m_stockGold;
	int						m_stockOil;
};

#endif