#ifndef __MANAGER_FACTORY_H__
#define __MANAGER_FACTORY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class ManagerComponent;
class MachineFactory;
class WarriorFactory;
class EnemyWarriorFactory;
class EnemyMachineFactory;
class Factory;
class ResourcesFactory;

class ManagerFactory
{
public:

	enum StateManagerFactory
	{
		ADD_FACTORY_WARRIOR,
		ADD_FACTORY_MACHINE,
		ADD_FACTORY_ENEMY_WARRIOR,
		ADD_FACTORY_ENEMY_MACHINE,
		ADD_FACTORY_GOLD,
		ADD_FACTORY_OIL,
		NOTHING
	};

	ManagerFactory();
	ManagerFactory(ManagerFactory& i_managerFactory);

	~ManagerFactory();
	
	void UpdateAllFactory(ManagerComponent& i_manager);

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerFactory& i_state);
	void SetPositionBuildFactory(Point i_point);
	Point GetPositionBuildFactory() const;

	void LaunchFillRegion(const Factory& i_factory, ManagerComponent& i_manager, int i_typeFactory);

	void AddOnScene(Factory& i_newObject, Point i_position);

	Size GetSizeFactoryMachine() const;
	Size GetSizeFactoryWarrior() const;

	void CreateFactory			(ManagerComponent& i_manager, int i_typeFactory);
	void CreateFactoryEnemy		(ManagerComponent& i_manager, int i_typeFactory);
	void CreateFactoryResources	(ManagerComponent& i_manager, int i_typeFactory);

private:
	std::vector<Factory*>	m_vecFactoryMachine;
	std::vector<Factory*>	m_vecFactoryWarrior;
	std::vector<Factory*>	m_vecFactoryEnemyWarrior;
	std::vector<Factory*>	m_vecFactoryEnemyMachine;
	std::vector<Factory*>	m_vecFactoryResources;

	StateManagerFactory				m_stateManagerFactory;
	Point							m_positionBuildFactory;

	Point m_positionNewFactory;
	Size  m_sizeNewFactory;

	Point m_positionOrigin;
};

#endif