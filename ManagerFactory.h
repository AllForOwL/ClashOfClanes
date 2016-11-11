#ifndef __MANAGER_FACTORY_H__
#define __MANAGER_FACTORY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Archer;
class ManagerComponent;
class MachineFactory;
class WarriorFactory;
class EnemyWarriorFactory;

class ManagerFactory
{
public:

	enum StateManagerFactory
	{
		ADD_FACTORY_WARRIOR,
		ADD_FACTORY_MACHINE,
		ADD_FACTORY_ENEMY_WARRIOR,
		ADD_FACTORY_ENEMY_MACHINE,
		NOTHING
	};

	ManagerFactory();
	ManagerFactory(ManagerFactory& i_managerFactory);

	~ManagerFactory();

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerFactory& i_state);
	void SetPositionBuildFactory(Point i_point);
	Point GetPositionBuildFactory() const;

private:
	std::vector<MachineFactory*>		m_vecFactoryMachine;
	std::vector<WarriorFactory*>		m_vecFactoryWarrior;
	std::vector<EnemyWarriorFactory*>	m_vecFactoryEnemyWarrior;
	
	StateManagerFactory				m_stateManagerFactory;
	Point							m_positionBuildFactory;
};

#endif