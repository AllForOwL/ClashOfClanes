#ifndef __MANAGER_ARMY_H__
#define __MANAGER_ARMY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Knight;
class ManagerComponent;
class EnemyWarrior;

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

private:
	std::vector<Knight*>		m_vecKnight;
	std::vector<EnemyWarrior*>	m_vecEnemy;

	StateManagerArmy		m_stateManagerArmy;

	Point					m_positionWarrior;

};

#endif