#ifndef __MANAGER_MACHINE_H__
#define __MANAGER_MACHINE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Archer;
class Tank;
class Car;
class ManagerComponent;
class MachineFactory;
class WarriorFactory;
class EnemyMachine;

class ManagerMachine
{
public:

	enum StateManagerMachine
	{
		ADD_TANK,
		ADD_CAR,
		ADD_ENEMY_OCTOPEDE,
		ADD_ENEMY_BRAIN,
		ADD_ENEMY_TURTLE,
		NOTHING
	};

	ManagerMachine();
	ManagerMachine(ManagerMachine& i_managerMachine);

	~ManagerMachine();

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerMachine& i_state);
	void SetPositionForMachine(Point i_pointBuildMachine);

private:
	std::vector<Tank*>			m_vecMachineTank;
	std::vector<Car*>			m_vecMachineCar;
	std::vector<EnemyMachine*>	m_vecEnemyMachine;
	StateManagerMachine		m_stateManagerMachine;

	Point	m_pointBuildMachine;
};

#endif