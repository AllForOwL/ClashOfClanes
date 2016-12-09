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
		WORKING,
		LISTEN,
		NOTHING
	};

	ResourcesFactory();
	ResourcesFactory(Point i_positionVisible, MapLayer& i_mapLayer, std::string i_filename);
	ResourcesFactory(ResourcesFactory& i_ResourcesFactory);

	~ResourcesFactory();

	virtual void Update(ManagerComponent& i_manager);

	StateFactoryResources& GetStateWarrior();

	void SetState(StateFactoryResources& i_stateWarrior);

	void StartProduction(int i_timeForComplete,  ManagerArmy::StateManagerArmy i_state);
	void FinishProduction(ManagerComponent& i_manager);

	void LoadProperties(ManagerComponent& i_manager);

	void LoadNameForSprites();
	bool DetermineCommand();

private:
	StateFactoryResources			m_stateResources;
};

#endif