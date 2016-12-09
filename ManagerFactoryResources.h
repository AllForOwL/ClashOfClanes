#ifndef __MANAGER_FACTORY_MACHINE_H__
#define __MANAGER_FACTORY_MACHINE_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class ManagerFactoryResources
{
public:

	enum StateManagerResources
	{
		UPDATE
	};

	ManagerFactoryResources();
	ManagerFactoryResources(ManagerFactoryResources& i_ManagerFactoryResources);

	~ManagerFactoryResources();

	void Update(ManagerComponent& i_manager);
	void UpdateAllFactoryResources(ManagerComponent& i_manager);

private:
	std::vector<ManagerFactoryResources*>	m_vecFactoryResources;
	StateManagerResources					m_stateManagerFactoryResources;
};

#endif