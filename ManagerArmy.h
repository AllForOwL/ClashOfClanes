#ifndef __MANAGER_ARMY_H__
#define __MANAGER_ARMY_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class Archer;

class ManagerArmy
{
public:

	enum StateManagerArmy
	{
		ADD_ARCHER,
		ADD_TANK,
		NOTHING
	};

	ManagerArmy();
	ManagerArmy(ManagerArmy& i_managerArmy);

	~ManagerArmy();

	void Update(GameScene& i_gameScene, ManagerComponent& i_manager);

	void SetState(StateManagerArmy& i_state);

private:
	std::vector<Archer*>	m_vecArcher;
	StateManagerArmy		m_stateManagerArmy;
};

#endif