#ifndef __MANAGER_ARMY_H__
#define __MANAGER_ARMY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Knight;
class ManagerComponent;
class EnemyWarrior;
class Warrior;
class InputComponent;

class ManagerArmy
{
public:

	enum StateManagerArmy
	{
		ADD_KNIGHT_BLACK,
		ADD_KNIGHT_BRONZE,
		ADD_KNIGHT_SILVER,
		ADD_ENEMY_BOWMAN,
		ADD_ENEMY_KNIGHT,
		ADD_ENEMY_WIZARD,
		ADD_ENEMY_PALADIN,
		NOTHING
	};

	ManagerArmy();
	ManagerArmy(ManagerArmy& i_managerArmy);

	~ManagerArmy();

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerArmy& i_state);

	void SetPositionForWarrior(Point i_positionWarrior);

	void LaunchFillRegion(const Warrior& i_warrior, ManagerComponent& i_manager, int i_typeWarrior);

	void CreateWarrior(ManagerComponent& i_manager, int i_typeObject, std::string i_nameFile);
	void CreateWarriorEnemy(ManagerComponent& i_manager, std::string i_typeEnemy);

	void UpdateAllWarrior(ManagerComponent& i_manager);

private:
	std::vector<Warrior*>	m_vecKnight;
	std::vector<Warrior*>	m_vecEnemy;

	StateManagerArmy		m_stateManagerArmy;

	Point					m_positionWarrior;

	Point	m_positionNewWarrior;
	Size	m_sizeNewWarrior;

};

#endif