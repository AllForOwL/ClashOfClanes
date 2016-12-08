#ifndef __MANAGER_MACHINE_H__
#define __MANAGER_MACHINE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Machine;
class ManagerComponent;

class ManagerMachine
{
public:

	enum StateManagerMachine
	{
		ADD_TANK,
		ADD_ENEMY_OCTOPEDE,
		ADD_ENEMY_BRAIN,
		ADD_ENEMY_TURTLE,
		NOTHING
	};

	ManagerMachine();
	ManagerMachine(ManagerMachine& i_managerMachine);

	~ManagerMachine();

	int GetQuentityTank() const;

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void CreateMachine(ManagerComponent& i_manager);
	void CreateMachineEnemy(ManagerComponent& i_manager, int i_typeObject, std::string i_nameFile);
	void UpdateAllMachine(ManagerComponent& i_manager);

	void SetState(StateManagerMachine& i_state);
	void SetPositionForMachine(Point i_pointBuildMachine);

	void LaunchFillRegion(const Machine& i_machine, ManagerComponent& i_manager, int i_typeMachine);
private:
	std::vector<Machine*>	m_vecMachineTank;
	std::vector<Machine*>	m_vecEnemyMachine;
	StateManagerMachine		m_stateManagerMachine;

	Point	m_pointBuildMachine;

	Point	m_positionNewMachine;
	Size	m_sizeNewMachine;
};

#endif