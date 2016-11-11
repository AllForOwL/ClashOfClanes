#ifndef __EnemyMachine_H__
#define __EnemyMachine_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class EnemyMachine : public Warrior
{
public:

	enum StateEnemyMachine
	{
		ATTACK,
		RUN,
		WANDER,
		HIDE,
		FIND_ACT,
		NOTHING
	};

	EnemyMachine();
	EnemyMachine(std::string i_typeEnemyMachine, MapLayer& i_parentMapLayer);
	EnemyMachine(EnemyMachine& heroGraphiComponent);

	~EnemyMachine();

	void ActAttack();
	void ActRun();
	void ActWander();
	void ActHide();

	virtual void Update(ManagerComponent& i_manager);

private:
	StateEnemyMachine	m_state;
};

#endif