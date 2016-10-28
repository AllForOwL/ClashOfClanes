#ifndef __MANAGER_FACTORY_H__
#define __MANAGER_FACTORY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Archer;
class ManagerComponent;
class MachineFactory;
class WarriorFactory;

class ManagerFactory
{
public:

	enum StateManagerFactory
	{
		ADD_FACTORY_WARRIOR,
		ADD_FACTORY_MACHINE,
		NOTHING
	};

	ManagerFactory();
	ManagerFactory(ManagerFactory& i_managerFactory);

	~ManagerFactory();

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerFactory& i_state);

private:
	std::vector<ManagerArmy*>		m_vecFactoryWarrior;
	std::vector<MachineFactory*>	m_vecFactoryMachine;
	StateManagerFactory				m_stateManagerFactory;
};

#endif