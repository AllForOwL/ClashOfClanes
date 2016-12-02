#ifndef __ENEMY_MACHINE_FACTORY_H__
#define __ENEMY_MACHINE_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerMachine.h"

USING_NS_CC;

class MapLayer;

class EnemyMachineFactory : public Factory
{
public:

	enum StateFactoryMachine
	{
		START_OCTOPEDE,
		START_BRAIN,
		START_TURTLE,
		WORKING,
		LISTEN,
		NOTHING
	};

	EnemyMachineFactory();
	EnemyMachineFactory(Point i_positionVisible, MapLayer& i_mapLayer);
	EnemyMachineFactory(EnemyMachineFactory& i_EnemyMachineFactory);

	~EnemyMachineFactory();

	virtual void Update(ManagerComponent& i_manager);

	StateFactoryMachine& GetState();
	void SetState(StateFactoryMachine& i_state);

	void LoadNameForSprites();

	bool DetermineCommand();

private:
	ManagerMachine::StateManagerMachine m_stateManagerMachine;
	StateFactoryMachine					m_stateMachine;
};

#endif